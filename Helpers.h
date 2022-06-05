#pragma once
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace Helpers
{
	inline int normalize_int(int int_to_norm, int norm_max) {
		if (int_to_norm >= norm_max)
		{
			return int_to_norm % norm_max;
		}
		else if (int_to_norm < 0)
		{
			return  norm_max + int_to_norm % norm_max;
		}
		else
		{
			return int_to_norm;
		}
	}
	
	inline std::pair<int, int> normalize_pair(std::pair<int, int> pair_to_norm, std::pair<int, int> pair_norm_max) { //Normalizing snake Fred
		return { normalize_int(pair_to_norm.first, pair_norm_max.first),normalize_int(pair_to_norm.second, pair_norm_max.second) };
	}

	inline std::string read_file_to_string(const std::string& fileName)
	{
		std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

		std::ifstream::pos_type fileSize = ifs.tellg();
		ifs.seekg(0, std::ios::beg);

		std::vector<char> bytes(fileSize);
		ifs.read(&bytes[0], fileSize);

		return std::string(&bytes[0], fileSize);
	}

	inline std::vector<bool> get_vectorSlice(std::vector<bool>& arr,
		int X, int Y)
	{
		auto start = arr.begin() + X;
		auto end = arr.begin() + Y + 1;

		std::vector<bool> result(Y - X + 1);

		copy(start, end, result.begin());
		return result;
	}
}

