#include "pch.h"
#include <windows.h>
#include "GUI.h"

intptr_t BaseAddress = (intptr_t)GetModuleHandle(NULL);

void send_attack_packet(int cid)
{
    intptr_t callpackettypeFunc = BaseAddress + 0xF8290;
    intptr_t callPacketInformation = BaseAddress + 0xF88A0;
    intptr_t callpacketcool = BaseAddress + 0xF8E40;
    __asm
    {
        PUSH 0xA1
        CALL callpackettypeFunc
        PUSH cid
        CALL callPacketInformation
        PUSH 1
        CALL callPacketInformation
        PUSH 1
        CALL callpacketcool

        ADD ESP, 16
    }
}

BOOL set_target(int cid)
{
    
    *(int*)(BaseAddress + 0x23FE64) = cid;

    send_attack_packet(cid);


    return true;
}
