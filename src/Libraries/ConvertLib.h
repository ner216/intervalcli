#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

namespace ConvertLib {

	bool isDigit(char val);
	int powTen(int n);
	int charToInt(char val[]);
	char intToChar(int num);
	int abs(int num);
	int timeMod(std::string);
	bool checkExistance(const std::filesystem::path& p, std::filesystem::file_status s = std::filesystem::file_status{});
	
}


