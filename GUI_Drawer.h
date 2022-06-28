#pragma once
#include "Window.h"
#include "Map.h"
#include "GUI_TextureHolder.h"
#include <deque>

class GUI_Drawer {
private:
	//std::vector<sf::Texture> terrainTextures;
	GUI_TextureHolder* current_TextureHolder;

	std::deque<std::string> my_CMD_Stack;
public:
	GUI_Drawer(GUI_TextureHolder* new_TextureHolder);

	void MapToWindow(Window* draw_to, Map* map_to_draw, int centering_rad);
	void InventoryToWindow(Window* draw_to, Player& current_player);
	void CMDToWindow(Window* draw_to);
	~GUI_Drawer();

	void CMD_PutToStack(std::string new_message);
};

