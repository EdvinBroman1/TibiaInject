#include "pch.h"
#include "Player.h"
#include <string>

intptr_t LocalPlayer = (intptr_t)(0x63FE40);
intptr_t pLocalPlayerMisc;
const intptr_t baseadr = (intptr_t)GetModuleHandle(NULL);

Player::Player()
{
    UpdateStats();
}

void Player::UpdateStats()
{
    this->fist_fight = *reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::FistSkill);
    this->club_fight = *reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::ClubSkill);
    this->sword_fight = *reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::SwordSkill);
    this->axe_fight = *reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::AxeSkill);
    this->distance_fight = *reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::DistanceSkill);
    this->shield = *reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::Shielding);
    this->fish = *reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::FishSkill);

    this->soul = *reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::Soul);
    this->max_mana = *reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::MaxMana);
    this->current_mana = *reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::Mana);
    this->magic_level = *reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::MagicLevel);
    this->level = *reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::Level);
    this->experience = *reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::Experience);

    this->max_health = *reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::MaxHealth);
    this->current_health = *reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::Health);
    this->creature_id = *reinterpret_cast<int*>(LocalPlayer + PlayerOffsets::CreatureID);
    pLocalPlayerMisc = getPlayerPointer(this->creature_id);
    this->Name = std::string((char*)(pLocalPlayerMisc + 0x4));
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

std::string Player::ToString() {
    return "Name: " + this->Name + "\nLevel: " + std::to_string(this->level) + "\nHealth: " + std::to_string(this->current_health) + " / " + std::to_string(this->max_health) + "\n";
}