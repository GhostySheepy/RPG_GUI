#pragma once
#include <array>
#include <vector>
#include "Item.h"
#include "Player.h"
class Chest
{
private:
	std::vector<Item> chest_inv;
	int chest_cap;
	int chest_coins;
	int chest_exp;
public:
	Chest();
	Chest(Item_Search_Plate dropped_item, int exp, int coin);
	Chest(std::vector<Item_Search_Plate> found_items, int exp, int coin);
	
	int get_coins(Player* cur_pl);
	int get_experience(Player* cur_pl);
	int get_cap();
	std::vector<Item> get_item_list();
	int pick_item(int item_pos, Player* cur_pl);
	bool is_empty();
};

