
#include "Map.h"
#include "DB.h"

namespace Custom_Init {
	Map* for_Map() {
        nlohmann::json current_branch = DB.Current_save["Chests"];
        /*      Chests      */    
        std::vector<Chest> chests_to_set;
        std::vector< std::pair<int, int> > chests_coords;
        std::vector <Item_Search_Plate> chest_insides;
        Item_Search_Plate new_plate;
        for (auto& element : current_branch) {
            chests_coords.insert(chests_coords.end(), std::make_pair(element["pos"][0], element["pos"][1]));
            for (auto& item : element["items"]) {
                chest_insides.insert(chest_insides.end(), Item_Search_Plate(item["type"], item["name"]));
            }
            chests_to_set.insert(chests_to_set.end(), Chest(chest_insides, element["exp"], element["coin"]));
        }
        /*     Enemies      */
        current_branch = DB.Current_save["Enemies"];
        std::vector<std::pair<int, int>> enemy_coords;

        npc::Director director;
        std::vector<std::shared_ptr<npc::Enemy>> enemyList;

        for (auto& element : current_branch) {

            enemy_coords.insert(enemy_coords.end(), std::make_pair(element["pos"][0], element["pos"][1]));
            npc::createEnemy(director, enemyList, std::make_pair(element["type"], element["level"]));
        }
        /*      Not_Enemies     */
        current_branch = DB.Current_save["Not_Enemies"];

        std::vector<std::pair<int, int>> not_enemy_coords;
        std::vector <npc::NotEnemy*> notEnemy_list;
        npc::NotEnemy* new_enemy = new npc::NotEnemy;
        for (auto& element : current_branch) {
            not_enemy_coords.insert(not_enemy_coords.end(), std::make_pair(element["pos"][0], element["pos"][1]));
           // new_enemy = new npc::NotEnemy;
            notEnemy_list.push_back(new_enemy);
        }
        /*      Player      */
        current_branch = DB.Current_save["Player"];
        std::pair<int, int> player_coords = std::make_pair(current_branch["pos"][0], current_branch["pos"][1]);
        /*      MAP INIT    */
        Map* new_map = new Map(player_coords, enemyList, enemy_coords, notEnemy_list, not_enemy_coords, chests_to_set, chests_coords);
        return new_map;
	}

}