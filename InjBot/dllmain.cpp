#include <windows.h>
#include <string.h>
#include "Player.h"
#include "GUI.h"
#include "Entity.h"
#include "Hook.h"

DWORD WINAPI InjectThread(HMODULE hModule)
{
    
    
    add_print("InjectBot 1.0", 5, 10, 255, 150, 150, 4);
    add_context_item("Supporter", 0x4000, "InjBot");
    add_context_item("Attacker", 0x4001, "InjBot");

    Player* player = new Player();
    enable_hooks();

    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }
        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            Position* posPtr = new Position(1004, 996, 7);
            player->WalkTo(posPtr);

        }
        if (GetAsyncKeyState(VK_NUMPAD5) & 1)
        {
            print_battle_list();
            add_print(std::to_string(get_battle_list_amount()), 300, 300, 255, 100, 255, 4);

        }
        if (GetAsyncKeyState(VK_NUMPAD9) & 1)
        {
            clear_prints();
            clear_battle_list();
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

