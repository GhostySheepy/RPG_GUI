#pragma once
#include "Player.h"

#include "Enemy.h"
#include "NotEnemy.h"
#include "NPC.h"
#include "Manager.h"
#include "DisplayMap.h"

#include "Custom_Init.h"
//#include "Helpers.h"
#include "SETTINGS.h"




Manager::Manager()
{
	current_window = new Window("RPG", sf::Vector2u(960, 540));
	timestep = sf::seconds(1. / SETTINGS.Framerate);
	elapsed_time = sf::seconds(0);
	current_EventManager = current_window->GetEventManager();
	current_TextureHolder = new GUI_TextureHolder();

	current_player = Player::getInstance("TEST");
	current_map = Custom_Init::for_Map();
}

void Manager::startNewGame()
{
	/*std::cout << "Welcome to the Game!\n" <<
		"Enter your name: ";

	std::string new_name;

	std::cin >> new_name;*/

	current_player = Player::getInstance("TEST");
	current_map = Custom_Init::for_Map();
}

void Manager::handleInput()
{
	auto inputsToProcess = current_EventManager->AskForTriggers(input_demand);
	current_map->moovePlayer(Helpers::get_vectorSlice(inputsToProcess, 0, 3));

}

void Manager::GameLoop()
{
	GUI_Drawer current_Drawer(current_TextureHolder);
	
	my_clock.restart();

	while (!current_window->IsDone()) {
		if (elapsed_time >= timestep) {
			elapsed_time -= timestep;

			current_window->Update(); // Get input
			handleInput();
			current_window->BeginDraw(); // Clear.
			current_Drawer.MapToWindow(current_window, current_map, 4);
			current_Drawer.InventoryToWindow(current_window);
			current_Drawer.CMDToWindow(current_window);
			current_window->EndDraw(); // Display.
		}
		elapsed_time += my_clock.restart();
	}
	current_window->Close();



/*	char choice;
	int fight_result;
	while (1)
	{
		DisplayMap::centerdedToCMD(3, current_map);
		std::cout << "Where you want to go: (f)orward, (b)ackward, (l)eft, (r)igt? Open (i)nventory. ";
		std::cin >> choice;
		std::cout << std::endl;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Oops, that input is invalid.  Please try again.\n";
		}
		else if (choice == 'i')
		{
			current_player->openInventory();
			continue;
		}
		{
			std::cin.ignore(32767, '\n');
			current_map->moovePlayer(choice);
			if (current_map->checkTileForEnemy(current_map->getPlayerPos()))
			{
				fight_result = startFight(current_map->getPlayerTileEnemy());
				if (fight_result == 1) {
					Chest enemy_loot(current_map->getPlayerTileEnemy()->inherit_item(), current_map->getPlayerTileEnemy()->get_level()*5, current_map->getPlayerTileEnemy()->get_level() * 10);
					current_map->burryPlayerTileNPC(enemy_loot);
				}
				else
				{
					break;
				}
			}
			if (current_map->checkTileForNPC(current_map->getPlayerPos()))
			{
				//npc::NotEnemy nurse;
				if (current_map->getPlayerTileNPC() == NULL) {
					std::cout << "ITS NULL" << std::endl;
				}
				else {
					std::cout << "ITS NOT NULL" << std::endl;
				}
				std::cout << current_map->getPlayerTileNPC()->getName() << std::endl;
				
				startHeal(current_map->getPlayerTileNPC());

			}
			if (current_map->checkTileForChest(current_map->getPlayerPos()))
			{
				std::cout << "Your tile has chest, do you want to open it? (y)es/ (n)o" << std::endl;
				std::cin >> choice;
				std::cout << std::endl;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					std::cout << "Oops, that input is invalid.  Please try again later.\n";
				}
				else
				{
					std::cin.ignore(32767, '\n');

					switch (choice) {
					case 'y':
						openChest(current_map->getPlayerTileChest());
						break;
					default:
						break;
					}
				}
			}
		}
	}*/
}

void Manager::continueGame()
{

}

bool Manager::startFight(std::shared_ptr<npc::Enemy> current_enemy) //0 player loose, 1 - player win
{
	//test segment
	std::cout << "Fight: " << current_player->getName() << " (" << current_player->getHealth() << " HP) VS "
		<< current_enemy->getName() << " (" << current_enemy->getHealth() << " HP)\n";

	bool player_turn = 1;

	while (1)
	{
		if (player_turn)  
		{
			std::cout << "Your turn!\n";

			std::cout << "Choose action: (a)ttack, (s)kip (default attack). \n";
			
			current_enemy->defence(current_player->attack());

			std::cout << "Enemy health: " << current_enemy->getHealth() << " HP\n";

			current_player->setHealth(current_player->getHealthRegen());

			if (!current_enemy->isAlive())
			{
				std::cout << "Enemy is dead\n"; // test, нужно открыть сундук, наверное
				
				return 1;
			}
		}
		else
		{
			std::cout << "Enemy turn!\n";

			current_player->defence(current_enemy->attack());

			std::cout << "Your health: " << current_player->getHealth() << " HP\n";

			if (!current_player->isAlive())
			{
				std::cout << "Noob, delete the game! ^_^ \n";
				return 0;
			}
		}
		player_turn = !player_turn;
	}
}

void Manager::startHeal(npc::NotEnemy* nurse)
{
	std::cout << "Hello. As you can see, I am a nurse. What are the nurses doing? Correct answer: heal." << std::endl;
	std::cout << "Let's count now the number of coins that you need to give me." << std::endl;

	if (current_player->getMoney() >= nurse->moneyForHeal())
	{
		std::cout << "Price is: " << nurse->moneyForHeal() << std::endl;
		std::cout << "Do you want to heal? ((y)es or (n)o)" << std::endl;

		char answer;

		while (1)
		{
			std::cin >> answer;
			if ('y' == answer)
			{
				nurse->heal();
				break;
			}
			else if ('n' == answer)
			{
				break;
			}
			std::cout << "Oops, something went wrong." << std::endl;
		}
	}
	else
	{
		std::cout << "You don't have enough money." << std::endl;
	}
}

void Manager::openChest(Chest* player_chest)
{
	int got_coins = player_chest->get_coins(current_player);
	int got_exp = player_chest->get_experience(current_player);
	if (got_coins != 0 || got_exp != 0) {
		std::cout << "You found and opened a new chest and got:  " << std::endl;
		std::cout << "\t" << got_coins << "-- coins;" << std::endl;
		std::cout << "\t" << got_exp << "-- experience;" << std::endl;
	}
	else {
		std::cout << "You opened same chest again, no coins for you!  " << std::endl;

	}
	
	
	int free_inv_place;

	std::string choice;
	int choice_int;
	std::vector<Item> chest_items;

	while (1) {
		if (player_chest->is_empty()) {
			std::cout << "There is no items inside!" << std::endl;
			std::cout << "Just write something to quit back to map" << std::endl;
			std::cin >> choice;
			std::cout << std::endl;
			current_map->burryPlayerTileChest();
			break;
		}
		else {
			std::cout << "Choose which item put to an inventory:" << std::endl;
			chest_items = player_chest->get_item_list();
			for (int i = 0; i < chest_items.size(); i++) {
				std::cout << i << "\t" << chest_items.at(i).getName() << ";" << std::endl;
			}
		}
		std::cout << "Or write (q) to quit back to map" << std::endl;
		choice_int = -1;
		std::cin >> choice;
		std::cout << std::endl;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Oops, that input is invalid.  Please try again.\n";
		}
		else
		{
			std::cin.ignore(32767, '\n');
			if (choice == "q") {
				if (player_chest->is_empty()) {
					current_map->burryPlayerTileChest();
				}
				break;
			}
			choice_int = stoi(choice);
			if (choice_int >= chest_items.size()) {
				std::cout << "There is no item with that num" << std::endl;
				continue;
			}
			free_inv_place = player_chest->pick_item(choice_int, current_player);
			if (free_inv_place < 0) {
				std::cout << "There is not enough space in inventory to put this item, you lack  " << free_inv_place << "to do this" << std::endl;;
			}
			else {
				std::cout << "Succsessful, free space:  " << free_inv_place << std::endl;
			}
		}
	}
}

void Manager::movePlayer()
{

}

void Manager::saveGame()
{
	
}

void Manager::exit()
{

}



Manager::~Manager()
{
	delete current_map;
	delete current_player;
}