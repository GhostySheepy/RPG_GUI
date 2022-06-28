#include "Item.h"

std::vector<ChangeList> Item::get_spec_change(nlohmann::json spec_change_list)
{
	std::vector<ChangeList> new_spec_change;
	ChangeList new_change_list{};
	for (auto& element : spec_change_list) {

		//std::cout << element << '\n';
		new_change_list.changed_z = element["z"];
		new_change_list.const_a = element["a"];
		new_change_list.const_b = element["b"];
		new_change_list.const_c = element["c"];
		new_change_list.dep_x = element["x"];
		new_change_list.dep_y = element["y"];
		new_change_list.z_min = element["z_min"];
		new_change_list.z_max = element["z_max"];

		new_spec_change.insert(new_spec_change.end(), new_change_list);
	}
	return new_spec_change;
}

void Item::apply_spec_change(Speclist *Player_Specs, std::vector<ChangeList> application, int mul)
{
	for (auto i : application) {
		(*Player_Specs).specs[i.changed_z] += (*Player_Specs).specs[i.dep_x] * i.const_a * mul + (*Player_Specs).specs[i.dep_y] * i.const_b * mul + i.const_c * mul;
		if ((*Player_Specs).specs[i.changed_z] < i.z_min) { (*Player_Specs).specs[i.changed_z] = i.z_min; }
		else if ((*Player_Specs).specs[i.changed_z] > i.z_max) { (*Player_Specs).specs[i.changed_z] = i.z_max; }
	}
}

void Item::transform_item(Item_Search_Plate transform_plate)
{
	nlohmann::json found_item = DB.Items_DB[transform_plate.type][transform_plate.name];
	name = transform_plate.name;
	description = found_item["description"];
	type = static_cast<Item_Types>(stoi(transform_plate.type));
	weight = found_item["weight"];
	level = found_item["level"];
	price = found_item["price"];
	durability = found_item["durability"];
	max_durability = found_item["max_durability"];
	texture = found_item["texture"];
	

	transform_to.type = found_item["transforms_to"]["type"];
	transform_to.name = found_item["transforms_to"]["name"];

	ChangeList new_change_list{};

	nlohmann::json spec_change_list = found_item["spec_change"];
	spec_change = get_spec_change(spec_change_list);

	spec_change_list = found_item["durability_coef"];
	durability_coef = get_spec_change(spec_change_list);
}

Item::Item(int item_type, std::string item_name)
{
	nlohmann::json found_item = DB.Items_DB[std::to_string(item_type)][item_name];
	//std::cout << found_item << "\n\n";
	name = item_name;
	description = found_item["description"];
	type = static_cast<Item_Types>(item_type);
	weight = found_item["weight"];
	level = found_item["level"];
	price = found_item["price"];
	durability = found_item["durability"];
	max_durability = found_item["max_durability"];
	texture = found_item["texture"]; 

	transform_to.type = found_item["transforms_to"]["type"];
	transform_to.name = found_item["transforms_to"]["name"];

	nlohmann::json spec_change_list = found_item["spec_change"];
	spec_change = get_spec_change(spec_change_list);

	spec_change_list = found_item["durability_coef"];
	durability_coef = get_spec_change(spec_change_list);
}

Item::Item(Item_Search_Plate item_plate)
{
	transform_item(item_plate);
}

Item::Item()
{
	Item_Search_Plate new_plate("5", "Wooden stick"),
	transform_item(new_plate);
}

std::string Item::getName()
{
	return name;
}

std::string Item::getDescription()
{
	return description;
}

Item_Types Item::getType()
{
	return type;
}

int Item::getWeight()
{
	return weight;
}

int Item::getTextureIter()
{
	return texture;
}

int Item::getDurability()
{
	return durability;
}

void Item::repairItem()
{
	durability = max_durability;
}

Speclist Item::useItem(Speclist Player_Specs)
{
	apply_spec_change(&Player_Specs, spec_change, 1);
	apply_spec_change(&Player_Specs, durability_coef, max_durability - durability);
	durability--;
	if (durability == transform_when) {
		transform_item(transform_to);
	}
	return Player_Specs;
}

Speclist Item::ShowSpecs(Speclist Player_Specs)
{
	apply_spec_change(&Player_Specs, spec_change, 1);
	apply_spec_change(&Player_Specs, durability_coef, max_durability - durability);
	if (durability == transform_when) {
		transform_item(transform_to);
	}
	return Player_Specs;
}

Item_Search_Plate::Item_Search_Plate()
{
	type = "5";
	name = "Wooden stick";
}

Item_Search_Plate::Item_Search_Plate(std::string new_type, std::string new_name)
{
	type = new_type;
	name = new_name;
}
