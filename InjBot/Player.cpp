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