#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

namespace ConvertLib {
	
	bool isLetter(char i);
	char upper(char i);
	char lower(char i);
	bool isDigit(char val);
	int powTen(int n);
	int charToInt(char digit);
	int charArrayToInt(char val[]);
	char intToChar(int num);
	int abs(int num);
	int timeMod(std::string);
	bool checkExistance(const std::filesystem::path& p);
	
}


