#include "pch.h"
#include "GUI.h"
#include "Hook.h"
#include "Includess.h"
#include "Attacker.h"
#include "Entity.h"
#include <string.h>
intptr_t BaseAdress = (intptr_t)GetModuleHandle(NULL);


DWORD WINAPI InjectThread(HMODULE hModule)
{
    add_print("Hello Injected", 5, 10, 30, 50, 150, 2);
    add_print("Print", 5, 30, 60, 50, 150, 2);

    Hook((void*)(BaseAdress + HookPrintAddy), print_text, 5);
    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }

        if (GetAsyncKeyState(VK_NUMPAD9) & 1)
        {
            clear_prints();
        }
        if (GetAsyncKeyState(VK_NUMPAD5) & 1)
        {
            populate_ent_list();
            print_ent_list();
            add_print(std::to_string(get_ent_amount()), 300, 300, 255, 100, 255, 4);

        }
        Sleep(10);
    }
    FreeLibraryAndExitThread(hModule, 0);

}







BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InjectThread, hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

