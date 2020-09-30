#include "Entity.h"
#include "Player.h"
#include "Addresses.h"
#include "GUI.h"
#include "Packet.h"

std::vector<Entity*> BattleList = std::vector<Entity*>();

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
	
	if (this->Z == player->Pos->Z && abs(this->X - player->Pos->X) <= 7 && abs(this->Y - player->Pos->Y) <= 5)
		return { true };
	else return { false };

}

void Entity::attack() {
	*reinterpret_cast<int*>(Client::BaseAddress + Control::RedSquare) = this->cid;
	send_attack_packet(this->cid);
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







