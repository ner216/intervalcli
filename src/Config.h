#include <iostream>
#include <string>
#include <fstream>
#include "Libraries/ConvertLib.h"

using namespace std;

struct Config {
	string timeZone;
	string soundDir;
	string worldClock;
	string editor;
	
	Config(string configPath="/etc/IntervalConfig.conf");
};
