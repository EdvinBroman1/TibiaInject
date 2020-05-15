#pragma once
#include "Position.h"
#include <string>

intptr_t getPlayerPointer(int creature_id);


struct PlayerSkills {
public:
	int FistSkill;
	int ClubSkill;
	int SwordSkill;
	int AxeSkill;
	int DistanceSkill;
	int	Shielding;
	int FishSkill;
	char unknown1[0x14];
	int Soul;
	int MaxMana;
	int Mana;
	char unknown2[0x8];
	int MagicLevel;
	int Level;
	int Experience;
	int MaxHealth;
	int	Health;

};

struct PlayerOffsets {
public:
	static const intptr_t CreatureID = 0x58;
	static const intptr_t PositionX = 0x24;
	static const intptr_t PositionY = 0x28;
    static const intptr_t PositionZ = 0x2C;
};

class Player {
public:
	int creature_id;
	PlayerSkills* Skills;
	uint32_t PlayerBase;
	Position* Pos;
	std::string Name;
	void Say(std::string msg, int id);
	bool WalkTo(Position* newPos);

	std::string ToString();

	Player();
};


