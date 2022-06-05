#pragma once
#include "Tile.h"


Tile::Tile()
{
	is_player_here = false;

	is_enemy_here = false;
	Enemy = NULL;

	is_not_enemy_here = false;
	NPC = NULL;
	
	is_chest_here = false;
	chest = NULL;

	type = Tile_Types::Sand;
}

void Tile::setTileType(Tile_Types type_to_set)
{
	type = type_to_set;
}

void Tile::setPlayer()
{
	is_player_here = true;
}

void Tile::unsetPlayer()
{
	is_player_here = false;
}

void Tile::setEnemy(std::shared_ptr<npc::Enemy> enemy_to_set)
{
	is_enemy_here = true;
	Enemy = enemy_to_set;
	is_not_enemy_here = false;
	NPC = NULL;
}

std::shared_ptr<npc::Enemy> Tile::unsetEnemy()
{
	is_enemy_here = false;
	return Enemy;
}

void Tile::setNPC(npc::NotEnemy* npc_to_set)
{
	is_not_enemy_here = true;
	NPC = npc_to_set;
	is_enemy_here = false;
	Enemy = NULL;
}

npc::NotEnemy* Tile::unsetNPC()
{
	is_enemy_here = false;
	return NPC;
}

void Tile::setChest(Chest* chest_to_set)
{
	is_chest_here = true;
	chest = chest_to_set;
}

Chest* Tile::unsetChest()
{
	is_chest_here = false;
	return chest;
}

Tile_Types Tile::getType()
{
	return type;
}

bool Tile::checkForPlayer()
{
	return is_player_here;
}

bool Tile::checkForEnemy()
{
	return is_enemy_here;
}

bool Tile::checkForNPC()
{
	return is_not_enemy_here;
}

bool Tile::checkForChest()
{
	return is_chest_here;
}

std::shared_ptr<npc::Enemy> Tile::returnEnemy()
{
	if (is_enemy_here) {
		return Enemy;
	}
	return NULL;
}

npc::NotEnemy* Tile::returnNPC()
{
	if (is_not_enemy_here) {
		return NPC;
	}
	return NULL;
}

Chest* Tile::returnChest()
{
	if (is_chest_here) {
		return chest;
	}
	return NULL;
}
