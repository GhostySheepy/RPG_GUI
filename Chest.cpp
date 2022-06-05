#include "Chest.h"

Chest::Chest()
{
	chest_cap = 0;
	chest_coins = 0;
	chest_exp = 0;
}

Chest::Chest(Item_Search_Plate dropped_item, int exp, int coin)
{
	chest_inv.insert(chest_inv.end(), Item(dropped_item));
	chest_cap = chest_inv.front().getWeight();
	chest_coins = coin;
	chest_exp = exp;
}

Chest::Chest(std::vector<Item_Search_Plate> found_items, int exp, int coin)
{
	chest_cap = 0;
	for (auto i : found_items) {
		chest_inv.insert(chest_inv.end(), Item(i));
		chest_cap += chest_inv.back().getWeight();
	}
	chest_coins = coin;
	chest_exp = exp;
}

int Chest::get_coins(Player* cur_pl)
{
	cur_pl->player_speclist.specs[static_cast<int>(Spec_Types::Coin)] += chest_coins;
	int curr_coins = chest_coins;
	chest_coins = 0;
	return curr_coins;
}

int Chest::get_experience(Player* cur_pl)
{
	cur_pl->player_speclist.specs[static_cast<int>(Spec_Types::Expreience)]+=chest_exp;
	int curr_exp = chest_exp;
	chest_exp = 0;
	return curr_exp;
}

int Chest::get_cap()
{
	return chest_cap;
}

std::vector<Item> Chest::get_item_list()
{
	return chest_inv;
}

int Chest::pick_item(int item_pos, Player* cur_pl) //returns free space after item is adeed, if space < 0, then item is left in chest
{
	int free_space = cur_pl->inv_max_capacity - cur_pl->inv_curr_capacity - chest_inv[item_pos].getWeight();
	if (free_space > 0){
		cur_pl->inventory.insert(cur_pl->inventory.end(), chest_inv[item_pos]);
		cur_pl->inv_curr_capacity += chest_inv.at(item_pos).getWeight();
		chest_cap -= chest_inv.at(item_pos).getWeight();
		chest_inv.erase(chest_inv.begin() + item_pos);
	}
	return free_space;
}

bool Chest::is_empty()
{
	return chest_cap == 0 ? 1 : 0;
}
