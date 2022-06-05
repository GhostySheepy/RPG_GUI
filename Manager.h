#pragma once

//#include "Menu.h"
#include "Map.h"
#include "Window.h"
#include "GUI_TextureHolder.h"
#include "GUI_Drawer.h"

#include "SETTINGS.h"

class Manager
{
private:
	Player* current_player;
	Map* current_map;

	Window* current_window;
	sf::Time timestep;
	sf::Time elapsed_time;
	sf::Clock my_clock;

	EventManager* current_EventManager;

	GUI_TextureHolder* current_TextureHolder;

	std::vector<sf::Keyboard::Key> input_demand = {
		SETTINGS.Key_WalkForward,
		SETTINGS.Key_WalkBacward,
		SETTINGS.Key_WalkLeft,
		SETTINGS.Key_WalkRight
	};

	void handleInput();
	


public:
	Manager();
	~Manager();

	void startNewGame();

	void GameLoop();

	void continueGame();

	bool startFight(std::shared_ptr<npc::Enemy> current_enemy); //0 player loose, 1 - player win

	void startHeal(npc::NotEnemy* nurse);

	void openChest(Chest* player_chest);

	void movePlayer();

	void saveGame();

	void exit();

};

