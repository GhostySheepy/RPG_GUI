#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Include/json.hpp"

#include "DB.h"
#include "Speclist.h"



enum class Item_Types {
	Armor, 
	Hat,
	Amplifier,
	Potion,
	Spell,
	Weapon,
	Magic_Weapon,
	Quest_Item,
	END
};

struct ChangeList  // z = a*x + b*y + c
{
	int changed_z;

	double const_a;
	int dep_x;

	double const_b;
	int dep_y;

	double const_c;

	double z_min;
	double z_max;
};

struct Item_Search_Plate {
	std::string type;
	std::string name;

	Item_Search_Plate();
	Item_Search_Plate(std::string new_type, std::string new_name);

};

class Item
{
private:
	std::string name;
	std::string description;

	Item_Types type;
	int weight;
	int level; //0 - the worst, 5 - the best
	int price;
	int texture;

	int durability;
	int max_durability;

	std::vector<ChangeList> spec_change;

	std::vector<ChangeList> durability_coef;

	Item_Search_Plate transform_to;
	int transform_when;

	std::vector <ChangeList> get_spec_change(nlohmann::json spec_change_list);
	void apply_spec_change(Speclist *Player_Specs, std::vector<ChangeList> application, int mul);

	void transform_item(Item_Search_Plate transform_plate);
	
public:
	Item();
	Item(int item_class, std::string item_name);
	Item(Item_Search_Plate item_plate);

	std::string getName();
	std::string getDescription();

	Item_Types getType();

	int getWeight();
	int getTextureIter();
	int getDurability();

	void repairItem();

	Speclist useItem(Speclist Player_Specs);
	Speclist ShowSpecs(Speclist Player_Specs);
};

