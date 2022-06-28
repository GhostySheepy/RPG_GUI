#pragma once

//#include "Menu.h"
#include "Map.h"
#include "Window.h"
#include "GUI_TextureHolder.h"
#include "GUI_Drawer.h"

#include "SETTINGS.h"

enum class Game_States {
	STANDART,
	FIGHT,
	STATE_COUNT
};

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

	std::vector<sf::Keyboard::Key> std_input_demand = {
		SETTINGS.Key_WalkForward,
		SETTINGS.Key_WalkBacward,
		SETTINGS.Key_WalkLeft,
		SETTINGS.Key_WalkRight,
		SETTINGS.Key_Action
	};

	std::vector<sf::Keyboard::Key> fight_input_demand = {
		SETTINGS.Key_Action,
		SETTINGS.Key_Skip,
		SETTINGS.Key_LeftHand,
		SETTINGS.Key_RightHand
	};


	Game_States current_State;

	int fight_input_await; //0 - message about choosing fight or skip turn, 1 -- choosing, 2 - message about weapon, 3 -- choosing, 4 -- processing

	void handleInput();

	std::vector<bool> spare_inputs;
	


public:
	Manager();
	~Manager();

	void startNewGame();

	void GameLoop();

	int FightStep(std::shared_ptr<npc::Enemy> current_enemy, GUI_Drawer* current_Drawer); //0 - player loose, 1 - player win, 2 - battle continues

	void HealStep(npc::NotEnemy* nurse, bool input, GUI_Drawer* current_Drawer);

	int ChestStep(Chest* player_chest, bool input, GUI_Drawer* current_Drawer);

};

