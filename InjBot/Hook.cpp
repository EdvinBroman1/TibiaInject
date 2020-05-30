#include <Windows.h>
#include "GUI.h"
#include "Addresses.h"

BOOL Hook(void* pTarget, void* ourFunct, int len)
{

    if (len < 5) {
        return false;
    }

    DWORD curProtection;
    VirtualProtect(pTarget, len, PAGE_EXECUTE_READWRITE, &curProtection);

    memset(pTarget, 0x90, len);

    DWORD relativeAddress = ((DWORD)ourFunct - (DWORD)pTarget) - 5;
    *(BYTE*)pTarget = 0xE8; // E8 == call E9 == JMP
    *(DWORD*)((DWORD)pTarget + 1) = relativeAddress;

    DWORD temp;
    VirtualProtect(pTarget, len, curProtection, &temp);
    return true;

}



void PrintHook()
{

    Hook((void*)(Client::BaseAddress + HookAddress::HookPrintAddy), print_text, 5);
}

void ContextMenuHook()
{
    Hook((void*)HookAddress::HookContextAdd, print_context, 5);
}

void ContextMenuSwitchHook()
{
    Hook((void*)HookAddress::HookContextMenuSwitch, ContextHandlerSaveRegisters, 5);
}

void CreateOptionButtonHook()
{
    Hook((void*)(Client::BaseAddress + 0x91609), hook_create_check_box, 7);
}

void enable_hooks()
{
    PrintHook();
    ContextMenuHook();
    ContextMenuSwitchHook();
   // CreateOptionButtonHook();

}