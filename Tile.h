#pragma once
#include <iostream>
#include "Player.h"
#include "Chest.h"
#include "Enemy.h"
#include "NPC.h"
#include "NotEnemy.h"

enum class Tile_Types {
	Ground,
	DeadTerritory,
	Mountian,
	Water,
	Sand
};
class Tile
{
private:
	Tile_Types type;

	bool is_player_here;
	
	bool is_enemy_here;
	std::shared_ptr<npc::Enemy> Enemy;
	bool is_not_enemy_here;
	npc::NotEnemy* NPC;
	bool is_chest_here;
	Chest *chest;

public:
	Tile();

	void setTileType(Tile_Types type_to_set);

	void setPlayer();
	void unsetPlayer();

	void setEnemy(std::shared_ptr<npc::Enemy> enemy_to_set);
	std::shared_ptr<npc::Enemy> unsetEnemy();

	void setNPC(npc::NotEnemy* npc_to_set);
	npc::NotEnemy* unsetNPC();

	void setChest(Chest* chest_to_set);
	Chest* unsetChest();

	Tile_Types getType();
	bool checkForPlayer();
	bool checkForEnemy();
	bool checkForNPC();
	bool checkForChest();

	std::shared_ptr<npc::Enemy> returnEnemy();
	npc::NotEnemy* returnNPC();
	Chest* returnChest();

};