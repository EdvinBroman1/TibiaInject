#include "pch.h"
#include <windows.h>
#include "GUI.h"
#include "Entity.h"

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

        ADD ESP, 0x10
    }
}

void Entity::attack() {
    *reinterpret_cast<int*>(BaseAddress + 0x23FE64) = this->cid;
    send_attack_packet(this->cid);
}
