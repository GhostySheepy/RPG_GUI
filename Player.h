#pragma once
#include <string>
#include <vector>

#include "Speclist.h"
#include "Item.h"

class Player
{
private:
	static Player* instance;

	Speclist player_speclist;

	std::string name;

	int inv_max_capacity = 20;
	int inv_curr_capacity  = 0;
	std::vector<Item> inventory;
	
	std::unordered_map<std::string, Item> equipment;
	/*std::unordered_map<std::string, Potion>*/

	Player(std::string n);

	friend class Chest;

public:

	static Player* getInstance(std::string n = "Player1");

	~Player();

	const std::string& getName();

	const int getMoney();

	const double getHealth();

	const double& getMaxHealth();

	const double getHealthRegen();

	void setHealth(double incoming_regen);

	bool isAlive();

	Speclist attack();
	Speclist attack(int* input_stage, std::vector<bool> inputs, std::string* outputs);

	void defence(Speclist enemy_speclist); // 0 - player is dead, 1 - is alive

	void showCharacteristics();

	void showInventory();

	void showEquipment();

	bool equipItem(Item equip_item); //0 - not succesful, 1 - succesful

	void openInventory();

};