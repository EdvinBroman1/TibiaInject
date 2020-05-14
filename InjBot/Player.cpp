#include "pch.h"
#include "Player.h"
#include <string>

intptr_t LocalPlayer = (intptr_t)(0x63FE40);
const intptr_t baseadr = (intptr_t)GetModuleHandle(NULL);


Player::Player() :
    fist_fight(*reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::FistSkill)),
    club_fight(*reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::ClubSkill)),
    sword_fight(*reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::SwordSkill)),
    axe_fight(*reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::AxeSkill)),
    distance_fight(*reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::DistanceSkill)),
    shield(*reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::Shielding)),
    fish(*reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::FishSkill)),

    soul(*reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::Soul)),
    max_mana(*reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::MaxMana)),
    current_mana(*reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::Mana)),
    magic_level(*reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::MagicLevel)),
    level(*reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::Level)),
    experience(*reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::Experience)),

    max_health(*reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::MaxHealth)),
    current_health(*reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::Health)),
    creature_id(*reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::CreatureID)),
    Name(std::string((char*)(PlayerBase + 0x4))),

    x_pos(*reinterpret_cast<int*>(PlayerBase + PlayerOffsets::PositionX)),
    y_pos(*reinterpret_cast<int*>(PlayerBase + PlayerOffsets::PositionY)),
    z_pos(*reinterpret_cast<int*>(PlayerBase + PlayerOffsets::PositionZ))
    {

    }




std::string Player::ToString() {
    return "Name: " + this->Name + "\nLevel: " + std::to_string(this->level) + "\nHealth: " + std::to_string(this->current_health) + " / " + std::to_string(this->max_health) + "\n";
}


void Player::Say(std::string msg, int id) {
    intptr_t funcd = baseadr + 0x73F0;

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

bool Player::WalkTo(Position* newPos) // later on hook Sorry not possible popup & there is no way popup to check if successful
{
    intptr_t functionadr = baseadr + 0xD0E20;
    int x = newPos->X - this->x_pos;
    int y = newPos->Y - this->y_pos;
    int z = newPos->Z - this->z_pos;
    __asm {
        push z
        push y
        push x

        call functionadr

    }
    return true;
}


intptr_t getPlayerPointer(int creature_id)
{
    intptr_t function_adr = baseadr + 0x5E720;
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