#include "Map.h"


Map::Map()
{
	map_size = std::make_pair(10, 10);
	map = new Tile * [map_size.first];
	for (int i = 0; i < map_size.first; i++) map[i] = new Tile[map_size.second];

	setDefaultTiles();
	setPlayer({ map_size.first / 2, map_size.second / 2 });
}

Map::Map(std::pair<int, int> player_coords, 
	std::vector<std::shared_ptr<npc::Enemy>> enemies_to_set, std::vector<std::pair<int, int>> enemies_coords, 
	std::vector <npc::NotEnemy*> npcs_to_set, std::vector<std::pair<int, int>> npc_coords,
	std::vector<Chest> chests_to_set, std::vector<std::pair<int, int>> chests_coords)
{
	map_size = std::make_pair(10, 10);
	map = new Tile * [map_size.first];
	for (int i = 0; i < map_size.first; i++) map[i] = new Tile[map_size.second];

	setDefaultTiles();
	setPlayer(player_coords);

	for (int i = 0; i < enemies_coords.size(); i++) {
		setEnemy(enemies_to_set.at(i), enemies_coords.at(i));
	}

	for (int i = 0; i < npc_coords.size(); i++) {
		setNPC(npcs_to_set.at(i), npc_coords.at(i));
	}

	chests = chests_to_set;
	for (int i = 0; (i < chests_coords.size() && i < chests_to_set.size()); i++) {
		setChest(&(chests.at(i)), chests_coords.at(i));
	}

}

Map::~Map()
{
	for (int i = 0; i < map_size.first; i++) delete[] map[i];
	delete[] map;
}

std::pair<int, int> Map::getSize()
{
	return map_size;
}

void Map::setEnemy(std::shared_ptr<npc::Enemy> NPC, std::pair<int, int> npc_coords)
{
	map[npc_coords.first][npc_coords.second].setEnemy(NPC);
}

void Map::unsetEnemy(std::pair<int, int> npc_coords)
{
	map[npc_coords.first][npc_coords.second].unsetEnemy();
}

void Map::setNPC(npc::NotEnemy* NPC, std::pair<int, int> npc_coords)
{
	map[npc_coords.first][npc_coords.second].setNPC(NPC);
}

void Map::unsetNPC(std::pair<int, int> npc_coords)
{
	map[npc_coords.first][npc_coords.second].unsetNPC();
}

void Map::setChest(Chest* chest_to_set, std::pair<int, int> chest_coords)
{
	map[chest_coords.first][chest_coords.second].setChest(chest_to_set);
}

void Map::unsetChest(std::pair<int, int> chest_coords)
{
	map[chest_coords.first][chest_coords.second].unsetChest();
	//maybe add some vector cleaning queue, but it could not make any sense....
}

void Map::setDefaultTiles()
{
	for (int x_coord = 0; x_coord < map_size.first; x_coord++)
	{
		for (int y_coord = 0; y_coord < map_size.second; y_coord++)
		{
			if (x_coord != 5&& y_coord != 5) {
				map[x_coord][y_coord].setTileType(Tile_Types::Ground);
			}
			else {
				map[x_coord][y_coord].setTileType(Tile_Types::DeadTerritory);
			}
			
		}
	}
}

void Map::setPlayer(std::pair<int, int> new_player_tile)
{

	player_pos = Helpers::normalize_pair(new_player_tile, map_size);
	map[player_pos.first][player_pos.second].setPlayer();
}

std::pair<int, int> Map::getPlayerPos()
{
	return player_pos;
}

void Map::moovePlayer(char dir) // (f)orward, (b)ackward, (l)eft, (r)igt
{
	std::pair<int, int> new_coords = player_pos;
	switch (dir)
	{
	case 'f':
		new_coords.second--;
		break;
	case 'b':
		new_coords.second++;
		break;
	case 'l':
		new_coords.first--;
		break;
	case 'r':
		new_coords.first++;
		break;
	default:
		break;
	}

	map[player_pos.first][player_pos.second].unsetPlayer();
	setPlayer(new_coords);
}

void Map::moovePlayer(std::vector<bool> dirs)
{
	char dir_chars[] = { 'f', 'b', 'l', 'r' };

	for (std::size_t i = 0; i < dirs.size(); ++i) {
		if (dirs[i]) {
			moovePlayer(dir_chars[i]);
		}
	}
}

Tile_Types Map::checkTileForType(std::pair<int, int> tile_to_check)
{
	return map[tile_to_check.first][tile_to_check.second].getType();
}

bool Map::checkTileForEnemy(std::pair<int, int> tile_to_check)
{
	return map[tile_to_check.first][tile_to_check.second].checkForEnemy();
}

bool Map::checkTileForNPC(std::pair<int, int> tile_to_check)
{
	return map[tile_to_check.first][tile_to_check.second].checkForNPC();
}

bool Map::checkTileForChest(std::pair<int, int> tile_to_check)
{
	return map[tile_to_check.first][tile_to_check.second].checkForChest();
}

std::shared_ptr<npc::Enemy> Map::getPlayerTileEnemy()
{
	return map[player_pos.first][player_pos.second].returnEnemy();
}

Chest* Map::getPlayerTileChest()
{
	return map[player_pos.first][player_pos.second].returnChest();
}

npc::NotEnemy* Map::getPlayerTileNPC()
{
	return map[player_pos.first][player_pos.second].returnNPC();
}

void Map::burryPlayerTileNPC(Chest dead_loot)
{
	chests.insert(chests.end(), dead_loot);
	setChest(&chests.at(chests.size() - 1), player_pos);
	unsetEnemy(player_pos);
}

void Map::burryPlayerTileChest()
{
	unsetChest(player_pos);
}

