#include "Player.h"
#include <iostream>
#include <ctime>


Player* Player::instance = 0;

Player* Player::getInstance(std::string n)
{
	if (instance == 0)
	{
		instance = new Player(n);
	}

	return instance;
}

Player::Player(std::string n) :
	name(n)
{
	player_speclist.specs[static_cast<int>(Spec_Types::Strength)] = 4;
	player_speclist.specs[static_cast<int>(Spec_Types::Perception)] = 4;
	player_speclist.specs[static_cast<int>(Spec_Types::Endurance)] = 4;
	player_speclist.specs[static_cast<int>(Spec_Types::Charisma)] = 4;
	player_speclist.specs[static_cast<int>(Spec_Types::Intelligence)] = 4;
	player_speclist.specs[static_cast<int>(Spec_Types::Agility)] = 4;
	player_speclist.specs[static_cast<int>(Spec_Types::Luck)] = 4;

	player_speclist.calculate_secondary_stats();
}

Player::~Player()
{
	
}

const std::string& Player::getName()
{
	return name;
}

const int Player::getMoney()
{
	return player_speclist.get(Spec_Types::Coin);
}

const int Player::getExp()
{
	return player_speclist.get(Spec_Types::Expreience);
}

const double Player::getHealth()
{
	return player_speclist.get(Spec_Types::Health);
}

const double Player::getHealthRegen()
{
	return player_speclist.get(Spec_Types::Health_regen);
}

const double Player::getDefaultDamage()
{
	Speclist tmp = player_speclist;

	if (equipment.find("Weapon") != equipment.end())
	{
		equipment["Weapon"].useItem(tmp);
	}

	return tmp.get(Spec_Types::Damage);
}

void Player::setHealth(double incoming_regen) //regen??
{
	if (player_speclist.get(Spec_Types::Health) + incoming_regen <
		player_speclist.get(Spec_Types::Max_health))
	{
		player_speclist.specs[static_cast<int>(Spec_Types::Health)] += incoming_regen;
	}
	else
	{
		player_speclist.specs[static_cast<int>(Spec_Types::Health)] =
			player_speclist.get(Spec_Types::Max_health);
	}
}

const double& Player::getMaxHealth()
{
	return player_speclist.specs[static_cast<int>(Spec_Types::Max_health)];
}

bool Player::isAlive()
{
	return getHealth() <= 0 ? 0 : 1;
}

Speclist Player::attack() {
	char choice;
	Speclist list_to_attack = player_speclist;

	if (player_speclist.get(Spec_Types::Max_action_points) -
		player_speclist.get(Spec_Types::Action_points) <
		player_speclist.get(Spec_Types::Action_points_regen))
	{
		player_speclist.specs[static_cast<int>(Spec_Types::Action_points)] =
			player_speclist.get(Spec_Types::Max_action_points);
	}
	else
	{
		player_speclist.specs[static_cast<int>(Spec_Types::Action_points)] +=
			player_speclist.get(Spec_Types::Action_points_regen);
	}

	while (player_speclist.specs[static_cast<int>(Spec_Types::Action_points)] > 0)
	{
		std::cout << "You have : " << player_speclist.get(Spec_Types::Action_points)
			<< " action points!\n";

		std::cin >> choice;

		if (choice == 'a')
		{
			if (equipment.find("Weapon1") == equipment.end())
			{
				if (equipment.find("Weapon2") == equipment.end())
				{
					std::cout << "Seems to be u don't have any weapon. Use your fists (skip).\n";
					continue;
				}
			}

			if (equipment.find("Weapon1") != equipment.end())
			{
				std::cout << "Weapon1: " << equipment["Weapon1"].getName() << ", DMG: " <<
					equipment["Weapon1"].getDescription() << std::endl;
			}

			if (equipment.find("Weapon2") != equipment.end())
			{
				std::cout << "Weapon2: " << equipment["Weapon2"].getName() << ", DMG: " <<
					equipment["Weapon2"].getDescription() << std::endl;
			}

			std::cout << "Your choice Weapon(1), Weapon(2):\n";
			char choice_weapon;

			while (1)
			{
				std::cin >> choice_weapon;

				if (choice_weapon == '1')
				{
					list_to_attack = equipment["Weapon1"].useItem(player_speclist);
					break;
				}
				else if (choice_weapon == '2')
				{
					list_to_attack = equipment["Weapon2"].useItem(player_speclist);
					break;
				}
				else
				{
					std::cout << "Incorret input, try again. \n";
					continue;
				}
			}
		}
		else if (choice == 's')
		{
			return list_to_attack;
		}
		else
		{
			std::cout << "Incorret input, try again. \n";
			continue;
		}

		player_speclist.specs[static_cast<int>(Spec_Types::Action_points)]--;
	}

	std::cout << "You don't have any action points.\n";
	return list_to_attack;
}

Speclist Player::attack(int* input_stage, std::vector<bool> inputs, std::string* outputs) {
	Speclist attacking_speclist = player_speclist;
	if (*input_stage == 0) {
		*outputs+= "Your turn! Press F to attack, or S to skip!\n";
		*input_stage = 1;
	}
	if (*input_stage == 1) {
		if (inputs.at(1) ) {
			*outputs += "Attacking with fists, really?\n";
			*input_stage = 4;
		}
		else if (inputs.at(0)) {
			if (equipment.find("Weapon1") == equipment.end() || equipment.find("Weapon2") == equipment.end()) {
				*outputs += "Attacking with fists, really?\n";
				*input_stage = 4;
			}
			else {
				*input_stage = 2;
			}

		}
	}
	if (*input_stage == 2) {
		*outputs += "Choose yor weapon! Q for left hand and E for weapon in right hand\n";
		*input_stage = 3;
	}
	if (*input_stage == 3) {
		if (inputs.at(2) || inputs.at(3)) {
			*input_stage = 4;
			if (inputs.at(2)) {
				attacking_speclist = equipment["Weapon1"].useItem(attacking_speclist);
			}
			else {
				attacking_speclist = equipment["Weapon2"].useItem(attacking_speclist);
			}
		}
	}

	//if (*input_stage == 4) { //processing and outputting }
	return attacking_speclist;
}

void Player::defence(Speclist enemy_speclist)
{
	Speclist spec_to_defence = player_speclist;
	
	if (equipment.find("Armor") != equipment.end())
	{
		equipment["Armor"].useItem(spec_to_defence);
	}
	if (equipment.find("Hat") != equipment.end())
	{
		equipment["Hat"].useItem(spec_to_defence);
	}

	int health_lost = enemy_speclist.get(Spec_Types::Damage);
	health_lost += static_cast<int>( (1 - (spec_to_defence.get(Spec_Types::Meele_resist) / 100)) * enemy_speclist.get(Spec_Types::Meele_damage));
	health_lost += static_cast<int>( (1-(spec_to_defence.get(Spec_Types::Deafening_resist) / 100)) * enemy_speclist.get(Spec_Types::Deafening_damage));
	health_lost += static_cast<int>( (1-(spec_to_defence.get(Spec_Types::Poision_resist) / 100)) * enemy_speclist.get(Spec_Types::Poision_damage));
	health_lost /= static_cast<int>(spec_to_defence.get(Spec_Types::Damage_resist));

	player_speclist.specs[static_cast<int>(Spec_Types::Health)] -= health_lost;
}

void Player::showCharacteristics()
{
	std::cout << "===///===///=== Characteristics ===///===///===\n";

	std::cout << "Name: " << Player::getName() << std::endl;

	Speclist info_spec = player_speclist;
	for (auto it = equipment.begin(); it != equipment.end(); it++)
	{
		it->second.useItem(info_spec);
	}

	std::cout << "Coin: " << info_spec.specs[0] << std::endl;
	std::cout << "Experience: " << info_spec.specs[1] << std::endl;
	std::cout << "Strength: " << info_spec.specs[2] << std::endl;
	std::cout << "Perception: " << info_spec.specs[3] << std::endl;
	std::cout << "Endurance: " << info_spec.specs[4] << std::endl;
	std::cout << "Charisma: " << info_spec.specs[5] << std::endl;
	std::cout << "Intelligence: " << info_spec.specs[6] << std::endl;
	std::cout << "Agility: " << info_spec.specs[7] << std::endl;
	std::cout << "Luck: " << info_spec.specs[8] << std::endl;
	std::cout << "Max_health: " << info_spec.specs[9] << std::endl;
	std::cout << "Health: " << info_spec.specs[10] << std::endl;
	std::cout << "Health_regen: " << info_spec.specs[11] << std::endl;
	std::cout << "Armor_class: " << info_spec.specs[12] << std::endl;
	std::cout << "Crit_reject: " << info_spec.specs[13] << std::endl;
	std::cout << "Damage_resist: " << info_spec.specs[14] << std::endl;
	std::cout << "Meele_resist: " << info_spec.specs[15] << std::endl;
	std::cout << "Deafening_resist: " << info_spec.specs[16] << std::endl;
	std::cout << "Poision_resist: " << info_spec.specs[17] << std::endl;
	std::cout << "Damage: " << info_spec.specs[18] << std::endl;
	std::cout << "Action_points: " << info_spec.specs[19] << std::endl;
	std::cout << "Max_action_points: " << info_spec.specs[20] << std::endl;
	std::cout << "Action_points_regen: " << info_spec.specs[21] << std::endl;
	std::cout << "Meele_damage: " << info_spec.specs[22] << std::endl;
	std::cout << "Deafening_damage: " << info_spec.specs[23] << std::endl;
	std::cout << "Poision_damage: " << info_spec.specs[24] << std::endl;
	std::cout << "Crit_chance: " << info_spec.specs[25] << std::endl;
	std::cout << "Crit_amplif: " << info_spec.specs[26] << std::endl;
	std::cout << "Carry_weight: " << info_spec.specs[30] << std::endl;
	/*for (int x = 0; x < static_cast<int>(Spec_Types::END); x++) 
	{
		std::cout << player_speclist.specs[x] << std::endl;
	}*/
}

void Player::showInventory()
{
	std::cout << "===///===///=== Inventory ===///===///===\n";
	int count = 1;

	if (inventory.empty())
	{
		std::cout << "Your inventory is empty, poor man.\n";
	}

	for (auto it = inventory.begin(); it != inventory.end(); it++, count++)
	{
		std::cout << "Slot [" << count << "]: " << it->getName() << std::endl;
	}
}

void Player::showEquipment()
{
	std::cout << "===///===///=== Equipment ===///===///===\n";
	
	if (equipment.empty())
	{
		std::cout << "You haven't equiped anything yet.\n";
	}

	for (auto it = equipment.begin(); it != equipment.end(); it++)
	{
		std::cout << it->first << ": " << it->second.getName() << std::endl;
	}
}

bool Player::equipItem(Item equip_item, int index_in_inv)
{
	std::string item_type = "Default";

	switch (static_cast<int>(equip_item.getType()))
	{
	case 0:
		item_type = "Armor";
		break;
	case 1:
		item_type = "Hat";
		break;
	case 5:
		item_type = "Weapon";
		break;
	default:
		return 0;
	}
	
	/*if (item_type == "Weapon")
	{
		if (equipment.find("Weapon1") == equipment.end())
		{
			item_type = "Weapon1";
		}
		else if (equipment.find("Weapon2") == equipment.end())
		{
			item_type = "Weapon2";
		}
		else
		{
			std::cout << "Which weapon you want to replace? Weapon(1), weapon(2)?\n";
			char weapon_choice;

			while (1)
			{
				std::cin >> weapon_choice;

				if (weapon_choice == '1')
				{
					item_type = "Weapon1";
					break;
				}
				else if (weapon_choice == '2')
				{
					item_type = "Weapon2";
					break;
				}
				else
				{
					std::cout << "Something went wrong.\n";
					continue;
				}
			}
		}
	}*/

	if (item_type != "Default" && equipment.find(item_type) != equipment.end())
	{
		inventory.push_back(equipment.find(item_type)->second);

		auto it = inventory.begin();
		int i = 0;
		while (i < index_in_inv)
		{
			i++;
			it++;
		}

		inventory.erase(it);

		equipment.erase(item_type);

		equipment.insert({ item_type, equip_item });
	}
	else if (item_type != "Default")
	{
		auto it = inventory.begin();
		int i = 0;
		while (i < index_in_inv)
		{
			i++;
			it++;
		}

		inventory.erase(it);

		equipment.insert({ item_type, equip_item });
		
	}

	/*std::cout << static_cast<int>(equip_item.getType());*/
	return 1;
}

//void Player::openInventory()
//{	
//	showInventory();
//	//showEquipment();
//
//	std::cout << "Choose item (number) you want to equip;show (i)nventory; show (e)quipment; show (c)haracteristics; (q) continue.\n";
//
//	char choice_inventory; 
//
//	while (1)
//	{
//		std::cin >> choice_inventory;
//
//		switch (choice_inventory)
//		{
//		case 'i':
//			showInventory();
//			break;
//		case 'e':
//			showEquipment();
//			break;
//		case 'c':
//			showCharacteristics();
//			break;
//		case 'q':
//			return;
//		default:
//			int ch_inv = choice_inventory - '0' - 1;
//
//			//std::cout << choice_inventory << " <- choice inventory\n" << ch_inv << " <- ch_inv\n";
//
//			if (ch_inv >= 0 && ch_inv < 10 && ch_inv < inventory.size())
//			{
//				if (equipItem(inventory[ch_inv]))
//				{
//					auto it = inventory.begin() + ch_inv;
//					inventory.erase(it);
//					std::cout << "Equiped correctly, now you can check your characteristics.\n";
//					break;
//				}
//				else
//				{
//					std::cout << "Somethint went wront (O_o). Try again.\n";
//					break;
//				}
//			}
//			else
//			{
//				std::cout << "Incorret input, try again. \n";
//				continue;
//			}
//		}	
//	}
//
//
//
//}

std::vector<Item>& Player::getInventory()
{
	return inventory;
}

std::unordered_map<std::string, Item> Player::getEquipment()
{
	return equipment;
}

Item Player::isEquiped(std::string item_type)
{
	Item ret_item;

	if (equipment.find(item_type) != equipment.end())
	{
		ret_item = equipment.find(item_type)->second;
	}

	return ret_item;
}
