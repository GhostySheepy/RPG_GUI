#pragma once

#include <utility>
#include <fstream>
#include <vector>

#include "Helpers.h"
#include "Tile.h"
#include "Custom_Json_Translate.h"


class Map
{
private:
	std::pair<int, int> map_size;
	Tile** map;

	std::pair<int, int> player_pos;

	std::vector<Chest> chests;

	void setDefaultTiles();
	void setPlayer(std::pair<int, int> player_tile);

	

public:
	Map();
	Map(std::pair<int, int> player_coords, 
		std::vector<std::shared_ptr<npc::Enemy>> enemies_to_set, std::vector < std::pair<int, int> > enemies_coords, 
		std::vector <npc::NotEnemy*> npcs_to_set, std::vector<std::pair<int, int>> npc_coords,
		std::vector<Chest> chests_to_set, std::vector <std::pair<int, int>> chest_coords);
	~Map();

	std::pair<int, int> getSize();

	void setEnemy(std::shared_ptr<npc::Enemy> NPC, std::pair<int, int> npc_coords);
	void unsetEnemy(std::pair<int, int> npc_coords);

	void setNPC(npc::NotEnemy* NPC, std::pair<int, int> npc_coords);
	void unsetNPC(std::pair<int, int> npc_coords);

	void setChest(Chest* chest_to_set, std::pair<int, int> chest_coords);
	void unsetChest(std::pair<int, int> chest_coords);

	std::pair<int, int> getPlayerPos();

	void moovePlayer(char dir);
	void moovePlayer(std::vector<bool> dirs);

	Tile_Types checkTileForType(std::pair<int, int> tile_to_check);
	bool checkTileForEnemy(std::pair<int, int> tile_to_check);
	bool checkTileForNPC(std::pair<int, int> tile_to_check);
	bool checkTileForChest(std::pair<int, int> tile_to_check);

	std::shared_ptr<npc::Enemy> getPlayerTileEnemy();
	Chest* getPlayerTileChest();
	npc::NotEnemy* getPlayerTileNPC();

	void burryPlayerTileNPC(Chest dead_loot);
	void burryPlayerTileChest();
};