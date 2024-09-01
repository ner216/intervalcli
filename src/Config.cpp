#include <iostream>
#include <filesystem>
#include "Config.h"

using namespace std;

Config::Config(string configPath){
	const int TotalConfLines = 8;
	bool configError = false;
	int counter = 0;
	string line;
	string soundCommand = "mpg123 -q ";
	string options[] = {"","","",""};
	
	//open config file:
	ifstream config(configPath);
	//copy odd # lines to options array (config values):
	if (config.is_open()){
		for (int i = 0; i < TotalConfLines; i++){
			getline(config, line);
			if (i % 2 != 0){
				options[counter] = line;
				counter++;
			}
		}
	}
	else {
		cerr << "Error: config file could not be opened [Config::Config]" << endl;
		std::exit(1);
	}
	config.close();
	
	this->timeZone = options[0];
	this->soundDir = soundCommand + " " + options[1];
	this->worldClock = options[2];
	this->editor = options[3] + " " + configPath;
	
	//variables created for testing validity:
	std::string editorName = options[3];
	std::string soundPath = options[1];
	
	//create path objects for possible locations of the chosen editor:
	std::filesystem::path p1("/usr/local/bin/" + editorName);
	std::filesystem::path p2("/usr/bin/" + editorName);
	std::filesystem::path p3("/usr/sbin/" + editorName);
	std::filesystem::path p4("/usr/local/sbin/" + editorName);
	
	//check if values in config file are testable:
	if (worldClock != "true" && worldClock != "false"){
		configError = true;
	}
	if (ConvertLib::timeMod(timeZone) == 0){
		configError = true;
	}
	if (ConvertLib::checkExistance(p1) == false && ConvertLib::checkExistance(p2) == false && ConvertLib::checkExistance(p3) == false){
		configError = true;
	}
	if (ConvertLib::checkExistance(soundPath) == false){
		configError = true;
	}
	//exit program if configError flag is true:
	if (configError == true){
		cerr << "Error: Config file options are invalid! Use: [intervalcli repair] to replace config!" << endl;
		std::exit(2);
	}
	
};
