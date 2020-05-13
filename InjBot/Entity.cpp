#include "pch.h"
#include "Entity.h"
#include <string>
#include "GUI.h"
#include "Player.h"
std::vector<Entity*> EntitiesOnScreen = std::vector<Entity*>();
intptr_t BaseAdresss = (intptr_t)GetModuleHandle(NULL);

Entity::Entity(int creature_id, std::string name, int h_precent, int x, int y, int z)
{
	this->cid = creature_id;
	this->Name = name;
	this->HealthPercent = h_precent;
	this->X = x;
	this->Y = y;
	this->Z = z;
}

std::string get_creature_name_by_cid(int cid)
{
	for (Entity* ent : EntitiesOnScreen)
	{
		if (ent->cid == cid)
		{
			return ent->Name;
		}
	}
	return "Couldn't Find ENT";
}


void populate_ent_list()
{ 
	//startBattleList  -> EndBattleList -> check parameters (x,y,z) -> add
	intptr_t BaseAdr = BaseAdresss + 0x23FEF8;
	intptr_t Offset = 0xA8;
	Player* player = new Player();

	for (int i = 0; i < 100; i++)
	{
		int creature_z = *(int*)(BaseAdr + (Offset * i) + 0x2C);
		int player_Z = *(int*)(getPlayerPointer(player->creature_id) + 0x2C);
			if (creature_z == player_Z) {
				EntitiesOnScreen.push_back(GetEntityByBaseAddress(BaseAdr + (Offset * i)));
			}
		else {
			continue;
		}
	}

}

void print_ent_list()
{
	int y = 30;
	for (Entity* ent : EntitiesOnScreen) {
		add_print(ent->Name, 50, y, 255, 255, 255, 4);
		y = y + 20;
	}

}

int get_ent_amount()
{
	return EntitiesOnScreen.size();

}

Entity* GetEntityByBaseAddress(uintptr_t BaseAddress)
{
	int cid = *(int*)BaseAddress;
	std::string name((char*)(BaseAddress + 0x4));
	int HealthProcent = *(int*)(BaseAddress + 0x88);
	int X = *(int*)(BaseAddress + 0x24);
	int Y = *(int*)(BaseAddress + 0x28);
	int Z = *(int*)(BaseAddress + 0x2C);
	Entity* ent = new Entity(cid, name, HealthProcent, X, Y, Z);
	return ent;
}





