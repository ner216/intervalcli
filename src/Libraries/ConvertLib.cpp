#include <iostream>
#include "ConvertLib.h"

namespace ConvertLib {

	bool isDigit(char val){
		char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
		for (int i = 0; i < 10; i++){
			if (digits[i] == val){
				return true;
			}
		}
		
		return false;
	}
	
	int powTen(int n){
		int result = 1;
		
		for (int i = 0; i < n; i++){
			result = result * 10;
		}
		
		return result;
	}
	
	int charToInt(char val[]){
		char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
		int result = 0;	
		int power = 0;
		
		for (int i = sizeof(&val)/sizeof(char); i >= 0 ; i--){
			for (int y = 0; y < 10; y++){
				if (val[i] == digits[y]){
					result = result + (y * powTen(power));
					power++;
				}
			}
		}
		
		return result;
	}
	
	char intToChar(int num){
		char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
		return digits[num];
	}

	//absolute value function for int
	int abs(int num){
		if (num > 0){
			return num;
		}
		else {
			return (num - (num*2));
		}
	}

	int timeMod(std::string zone){		//returns 0 if no match is found
		const int totalZones = 8;		//change this if zones are added
		std::string zones[] = {"EST","EDT","CST","CDT","MST","MDT","PST","PDT"};
		int mods[] = {-5, -4, -6, -5, -7, -6, -8, -7};
		
		for (int i = 0; i < totalZones; i++){
			if (zone == zones[i]){
				return mods[i];
			}
		}
		
		return 0;
	}
	
	bool checkExistance(const std::filesystem::path& p, std::filesystem::file_status s){
		if (std::filesystem::status_known(s) ? std::filesystem::exists(s) : std::filesystem::exists(p)){
			return true;
		}
		else {
			return false;
		}
	}

}
