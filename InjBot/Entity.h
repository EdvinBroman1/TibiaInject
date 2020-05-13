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
};


Entity* GetEntityByBaseAddress(uintptr_t BaseAddress);

void populate_ent_list();
void print_ent_list();
int get_ent_amount();
//char* get_creature_name_by_cid(int cid);