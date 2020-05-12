#include <Windows.h>
#include "pch.h"

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
