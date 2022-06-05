#pragma once
#include <fstream>
#include "Map.h"
#include "Helpers.h"


namespace DisplayMap
{

	int pieceToFile(std::pair<int, int> from, std::pair<int, int> to, Map* map_to_print)
	{

		std::ofstream fout("map.txt");

		if (!fout)
		{
			std::cout << "Cant open file\n\n";
			return -1;
		}
		else
		{
			std::cout << "File succsesfully opened\n\n";
		}

		int x_coord;
		int y_coord;



		for (x_coord = from.first; x_coord < to.first; x_coord++)
		{
			for (y_coord = from.second; y_coord < to.second; y_coord++)
			{
				fout << "______________";
			}
			fout << '\n';

			for (y_coord = from.second; y_coord < to.second; y_coord++)
			{
				switch (static_cast<int>(map_to_print->checkTileForType({ x_coord, y_coord })))
				{
				case 0:
					fout << "|   Ground    ";
					break;
				case 1:
					fout << "|  DeadTerr   ";
					break;
				case 2:
					fout << "|  Mountian   ";
					break;

				case 3:
					fout << "|   Water     ";
					break;
				case 4:
					fout << "|   Sand      ";
					break;
				default:
					fout << "| AAAAAAAAAAA ";
					break;
				}
			}
			fout << "| \n";

			for (y_coord = from.second; y_coord < to.second; y_coord++)
			{
				if (map_to_print->getPlayerPos() == std::make_pair(x_coord, y_coord)) {
					fout << "|   PLAYER    ";
				}
				else
				{
					fout << "|             ";
				}
			}
			fout << "| \n";

			for (y_coord = from.second; y_coord < to.second; y_coord++)
			{
				if (map_to_print->checkTileForNPC({ x_coord, y_coord })) {
					fout << "|    NPC      ";
				}
				else
				{
					fout << "|             ";
				}
			}
			fout << "| \n";

			for (y_coord = from.second; y_coord < to.second; y_coord++)
			{
				if (map_to_print->checkTileForChest({ x_coord, y_coord })) {
					fout << "|   Chest     ";
				}
				else
				{
					fout << "|             ";
				}
			}
			fout << "| \n";
		}
		for (y_coord = from.second; y_coord < to.second; y_coord++)
		{
			fout << "______________";
		}
		fout << '\n';
		return 0;

	}

	int wholeMapToFile(Map* map_to_print)
	{
		return pieceToFile({ 0, 0 }, map_to_print->getSize(), map_to_print);;
	}

	int centerdedToCMD(int centering_rad, Map* map_to_print)
	{
		using Helpers::normalize_int;
		int x_coord;
		int y_coord;

		std::pair<int, int> player_pos = map_to_print->getPlayerPos();

		std::pair<int, int> from = { player_pos.first - centering_rad, player_pos.second - centering_rad };
		std::pair<int, int> to = { player_pos.first + centering_rad + 1, player_pos.second + centering_rad + 1 };

		for (x_coord = from.first; x_coord < to.first; x_coord++)
		{
			for (y_coord = from.second; y_coord < to.second; y_coord++)
			{
				std::cout << "______________";
			}
			std::cout << '\n';

			/*for (y_coord = from.second; y_coord < to.second; y_coord++) //Debugging Snake
			{
				std::cout << "| " << x_coord << "  " << y_coord<< "  " << Helpers::normalize_int(x_coord, map_size.first) << "  " << Helpers::normalize_int(y_coord, map_size.second);
			}
			std::cout << "| \n"*/

			for (y_coord = from.second; y_coord < to.second; y_coord++)
			{

				switch(static_cast<int>(map_to_print->checkTileForType(Helpers::normalize_pair({x_coord, y_coord}, map_to_print->getSize()))))
				{
				case 0:
					std::cout << "|   Ground    ";
					break;
				case 1:
					std::cout << "|  DeadTerr   ";
					break;
				case 2:
					std::cout << "|  Mountian   ";
					break;

				case 3:
					std::cout << "|   Water     ";
					break;
				case 4:
					std::cout << "|   Sand      ";
					break;
				default:
					std::cout << "| AAAAAAAAAAA ";
					break;
				}
			}
			std::cout << "| \n";

			for (y_coord = from.second; y_coord < to.second; y_coord++)
			{
				if (map_to_print->getPlayerPos() == Helpers::normalize_pair({ x_coord, y_coord }, map_to_print->getSize())) {
					std::cout << "|   PLAYER    ";
				}
				else
				{
					std::cout << "|             ";
				}
			}
			std::cout << "| \n";

			for (y_coord = from.second; y_coord < to.second; y_coord++)
			{
				if(map_to_print->checkTileForEnemy(Helpers::normalize_pair({ x_coord, y_coord }, map_to_print->getSize())))
				{
					std::cout << "|    ENEMY    ";
				}
				else
				{
					std::cout << "|             ";
				}
			}
			std::cout << "| \n";

			for (y_coord = from.second; y_coord < to.second; y_coord++)
			{
				if (map_to_print->checkTileForNPC(Helpers::normalize_pair({ x_coord, y_coord }, map_to_print->getSize())))
				{
					std::cout << "|    NPC      ";
				}
				else
				{
					std::cout << "|             ";
				}
			}
			std::cout << "| \n";

			for (y_coord = from.second; y_coord < to.second; y_coord++)
			{
				if (map_to_print->checkTileForChest(Helpers::normalize_pair({ x_coord, y_coord }, map_to_print->getSize())))
				{
					std::cout << "|   Chest     ";
				}
				else
				{
					std::cout << "|             ";
				}
			}
			std::cout << "| \n";
		}
		for (y_coord = from.second; y_coord < to.second; y_coord++)
		{
			std::cout << "______________";
		}
		std::cout << '\n';
		return 0;
	}

}


