#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Config {
	string timeZone;
	string soundDir;
	string worldClock;
	string editor;
	
	Config(string configPath="/etc/IntervalConfig.conf");
};
