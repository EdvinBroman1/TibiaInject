#include "pch.h"
#include "Entity.h"
#include <string>
#include "GUI.h"
#include "Player.h"

std::vector<Entity*> BattleList = std::vector<Entity*>();
intptr_t BaseAdresss = (intptr_t)GetModuleHandle(NULL);

Entity::Entity(int creature_id, std::string name, int h_precent, int x, int y, int z) :
	cid(creature_id), Name(name), HealthPercent(h_precent), X(x), Y(y), Z(z) {
};


int Entity::get_cid()
{
	return this->cid;
}

std::string Entity::get_name()
{
	return this->Name;
}

void Entity::add_to_battle_list()
{
	BattleList.push_back(this);
}

bool Entity::isOnScreen()
{
	Player* player = new Player();

	if (this->Z == player->z_pos && abs(this->X - player->x_pos) <= 7 && abs(this->Y - player->y_pos) <= 5)
		return { true };
	else return { false };

}


void print_battle_list()
{
	int y = 30;
	for (Entity* ent : BattleList) {
		if(ent->isOnScreen())
		add_print(ent->Name, 50, y, 255, 255, 255, 4);
		y = y + 20;
	}

}

void clear_battle_list()
{

	BattleList.clear();
	BattleList.shrink_to_fit();
}

int get_battle_list_amount()
{
	return BattleList.size();
}







