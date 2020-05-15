
#include "Player.h"
#include "Addresses.h"



Player::Player() :
    Skills(reinterpret_cast<PlayerSkills*>(Client::BaseAddress + Self::LocalPlayer)),
    creature_id(*reinterpret_cast<int*>(Client::BaseAddress + Self::LocalPlayer + PlayerOffsets::CreatureID)),
    PlayerBase(getPlayerPointer(creature_id)),
    Pos(reinterpret_cast<Position*>(PlayerBase + PlayerOffsets::PositionX))
{
}

std::string Player::ToString() {
    return "Name: " + this->Name + "\nLevel: " + std::to_string(this->Skills->Level) + "\nHealth: " + std::to_string(this->Skills->Health) + " / " + std::to_string(this->Skills->MaxHealth) + "\n";
}


void Player::Say(std::string msg, int id) {
    intptr_t funcd = Client::BaseAddress + 0x73F0;

    char* ca = new char[msg.size() + 1];
    std::copy(msg.begin(), msg.end(), ca);
    ca[msg.size()] = '\0';

    __asm {
        push ca
        push id
        call funcd
        add esp, 0x8
    }

    delete[] ca;
}

bool Player::WalkTo(Position* newPos) 
{
    intptr_t functionadr = Client::BaseAddress + 0xD0E20;
    int x = newPos->X - this->Pos->X;
    int y = newPos->Y - this->Pos->Y;
    int z = newPos->Z - this->Pos->Z;
    __asm {
        push z
        push y
        push x
        call functionadr
    }
    if (newPos->X == this->Pos->X && newPos->Y == this->Pos->Y && newPos->Z == this->Pos->Z)
        return true;
    else
        return false;
}


intptr_t getPlayerPointer(int creature_id)
{
    intptr_t function_adr = Client::BaseAddress + 0x5E720;
    intptr_t pointr = 0x0;

    __asm
    {
        MOV EAX, creature_id
        PUSH eax
        CALL function_adr;
        ADD ESP, 0x4
            mov pointr, eax
    }
    return pointr;
}