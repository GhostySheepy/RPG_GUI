#pragma once
#include "Window.h"
#include "Map.h"
#include "GUI_TextureHolder.h"

class GUI_Drawer {
private:
	//std::vector<sf::Texture> terrainTextures;
	GUI_TextureHolder* current_TextureHolder;
public:
	GUI_Drawer(GUI_TextureHolder* new_TextureHolder);

	void MapToWindow(Window* draw_to, Map* map_to_draw, int centering_rad);
	void InventoryToWindow(Window* draw_to);
	void CMDToWindow(Window* draw_to);
	~GUI_Drawer();
};

