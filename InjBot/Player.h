#pragma once
#include <string>

class Player {
private:
	enum PlayerOffsets {
		FistSkill = 0x0,
		ClubSkill = 0x4,
		SwordSkill = 0x8,
		AxeSkill = 0xC,
		DistanceSkill = 0x10,
		Shielding = 0x14,
		FishSkill = 0x18,

		Soul = 0x30,
		MaxMana = 0x34,
		Mana = 0x38,

		MagicLevel = 0x44,
		Level = 0x48,
		Experience = 0x4C,
		MaxHealth = 0x50,
		Health = 0x54,

		CreatureID = 0x58
	};
public:
	Player();
	int getID();
	void UpdateStats();
	std::string ToString();
	//stats
	int fist_fight;
	int club_fight;
	int sword_fight;
	int axe_fight;
	int distance_fight;
	int shield;
	int fish;

	int soul;
	int max_mana;
	int current_mana;

	int magic_level;
	int level;
	int experience;
	int max_health;
	int current_health;

	int creature_id;

	std::string Name;

};


intptr_t getPlayerPointer(int creature_id);