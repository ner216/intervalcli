#include <iostream>
#include "Config.h"

using namespace std;

Config::Config(string configPath){
	string soundCommand = "mpg123 -q ";
	const int TotalConfLines = 8;
	int counter = 0;
	string line;
	string options[] = {"","","",""};
	
	ifstream config(configPath);
	
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
	}
	config.close();
	
	this->timeZone = options[0];
	this->soundDir = soundCommand + " " + options[1];
	this->worldClock = options[2];
	this->editor = options[3] + " " + configPath;
	
};
