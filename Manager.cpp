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

	fight_input_await = 0;

	current_State = Game_States::STANDART;
}

void Manager::startNewGame()
{
	current_map = Custom_Init::for_Map();
}

void Manager::handleInput()
{
	if (current_State == Game_States::STANDART) {
		auto inputsToProcess = current_EventManager->AskForTriggers(std_input_demand);
		current_map->moovePlayer(Helpers::get_vectorSlice(inputsToProcess, 0, 3));
		spare_inputs = Helpers::get_vectorSlice(inputsToProcess, 4, 4);
	}
	else {
		auto inputsToProcess = current_EventManager->AskForTriggers(fight_input_demand);
		spare_inputs = Helpers::get_vectorSlice(inputsToProcess, 0, 3);
	}

	
}

void Manager::GameLoop()
{
	GUI_Drawer current_Drawer(current_TextureHolder);
	
	my_clock.restart();

	std::pair<int, int> previous_pos = current_map->getSize();

	int fight_result;

	while (!current_window->IsDone()) {
		if (elapsed_time >= timestep) {
			elapsed_time -= timestep;

			current_window->Update(); // Get input
			handleInput();
			if (current_State == Game_States::STANDART) {
				if (current_map->getPlayerPos() != previous_pos) {
					previous_pos = current_map->getPlayerPos();

					if (current_map->checkTileForEnemy(current_map->getPlayerPos())) {
						current_State = Game_States::FIGHT;
						fight_input_await = 0;
						current_Drawer.CMD_PutToStack("You are figthing with: " + current_map->getPlayerTileEnemy()->getName() + "  (" + std::to_string(current_map->getPlayerTileEnemy()->getHealth()) + " HP)\n");
					}
					if (current_map->checkTileForNPC(current_map->getPlayerPos())) {
						current_Drawer.CMD_PutToStack("Hey! You, there! I could heal you for only  " + std::to_string(current_map->getPlayerTileNPC()->moneyForHeal()) + ".\n Press F to do that\n");
					}
					if (current_map->checkTileForChest(current_map->getPlayerPos())) {
						current_Drawer.CMD_PutToStack("You are in a tile with chest. Press F to collect some loot\n");
					}

					/*if (current_map->checkTileForChest(current_map->getPlayerPos())) {
						std::cout << "Your tile has chest, do you want to open it? (y)es/ (n)o" << std::endl;
						openChest(current_map->getPlayerTileChest());
					}*/
				}
				if (current_map->checkTileForNPC(current_map->getPlayerPos())) {
					HealStep(current_map->getPlayerTileNPC(), spare_inputs.at(0), &current_Drawer);
				}
				else if (current_map->checkTileForChest(current_map->getPlayerPos())) {
					ChestStep(current_map->getPlayerTileChest(), spare_inputs.at(0), &current_Drawer);
				}
				

			}
			else if (current_State == Game_States::FIGHT) {
				fight_result = FightStep(current_map->getPlayerTileEnemy(), &current_Drawer);
				if (fight_result == 1) {
					Chest enemy_loot(current_map->getPlayerTileEnemy()->inherit_item(), current_map->getPlayerTileEnemy()->get_level() * 5, current_map->getPlayerTileEnemy()->get_level() * 10);
					current_map->burryPlayerTileNPC(enemy_loot);
					current_State = Game_States::STANDART;
				}
				else if (fight_result == 0) break;
			}


			
			current_window->BeginDraw(); // Clear.

			current_Drawer.MapToWindow(current_window, current_map, 4);
			current_Drawer.InventoryToWindow(current_window);
			current_Drawer.CMDToWindow(current_window);

			current_window->EndDraw(); // Display.
		}
		elapsed_time += my_clock.restart();
	}
	current_window->Close();
}

int Manager::FightStep(std::shared_ptr<npc::Enemy> current_enemy, GUI_Drawer* current_Drawer) //0 player loose, 1 - player win
{
	std::string to_output;
	Speclist player_attacking_list = current_player->attack(&fight_input_await, spare_inputs, &to_output);
	if (to_output != "") {
		current_Drawer->CMD_PutToStack(to_output);
		to_output = "";
	}
	if (fight_input_await == 4) {
		fight_input_await = 0;
		current_enemy->defence(player_attacking_list);

		current_Drawer->CMD_PutToStack("Enemy health : " + std::to_string(current_enemy->getHealth()) + "\n");

		current_player->setHealth(current_player->getHealthRegen());

		if (!current_enemy->isAlive())
		{
			current_Drawer->CMD_PutToStack("Yoy`ve killed enemy, now you can collect his heritance by pressing F \n");

			return 1;
		}
		current_Drawer->CMD_PutToStack("Now Enemy`s turn, watch your HP falling! \n");

		current_player->defence(current_enemy->attack());

		if (!current_player->isAlive())
		{
			current_Drawer->CMD_PutToStack("Noob, delete the game! ^_^ \n");
			return 0;
		}
	}
	return 2;
}

void Manager::HealStep(npc::NotEnemy* nurse, bool input, GUI_Drawer* current_Drawer)
{
	if (input == true) {
		if (current_player->getMoney() >= nurse->moneyForHeal())
		{
			nurse->heal();
			current_Drawer->CMD_PutToStack("Here  ya` go! \n");
		}
		else
		{
			current_Drawer->CMD_PutToStack("You don't have enough money. \n");
		}
	}
}

int Manager::ChestStep(Chest* player_chest, bool input, GUI_Drawer* current_Drawer)
{
	
	std::vector<Item> chest_items = player_chest->get_item_list();
	if (input == true) {
		int got_coins = player_chest->get_coins(current_player);
		int got_exp = player_chest->get_experience(current_player);
		if (got_coins != 0 || got_exp != 0) {
			current_Drawer->CMD_PutToStack("\nYou found " + std::to_string(got_coins) + " coins and " + std::to_string(got_exp) + "\n");
			current_Drawer->CMD_PutToStack("Now press F again to collect items!\n");
			for (int i = 0; i < chest_items.size(); i++) {
				std::cout << i << "\t" << chest_items.at(i).getName() << " : " << chest_items.at(i).getTextureIter() << std::endl;
			}
			return 0;
		}
		else {
			int free_inv_place;

			int count = 0;
			std::vector<Item> chest_items;

			while (1) {

				if (player_chest->is_empty()) {
					current_map->burryPlayerTileChest();
					break;
				}

				free_inv_place = player_chest->pick_item(0, current_player);
				if (free_inv_place < 0) {
					break;
				}
			}
			return 0;
		}
	}
}


Manager::~Manager()
{
	delete current_map;
	delete current_player;
}