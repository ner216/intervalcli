#include <iostream>
#include <string>
#include <fstream>
#include "Libraries/ConvertLib.h"

struct Config {
	std::string timeZone;
	std::string soundDir;
	std::string worldClock;
	std::string editor;
	
	Config(std::string configPath="/etc/IntervalConfig.conf");
};
