#include "windows.h"
#include "Addresses.h"
void send_attack_packet(int cid)
{
    intptr_t callpackettypeFunc = Client::BaseAddress + 0xF8290;
    intptr_t callPacketInformation = Client::BaseAddress + 0xF88A0;
    intptr_t callpacketcool = Client::BaseAddress + 0xF8E40;
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