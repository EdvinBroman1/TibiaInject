#include <vector>
#include <string>

class Entity {
public:
	int cid;
    std::string Name;
	int HealthPercent;
	int X;
	int Y;
	int Z;
	Entity(int creature_id, std::string name, int h_precent, int x, int y, int z);
	int get_cid();
	std::string get_name();
	void add_to_battle_list();
	bool isOnScreen();
	void attack();
};


void print_battle_list();
int get_battle_list_amount();
void clear_battle_list();