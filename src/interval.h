#include <iostream>
#include <unistd.h>
#include <time.h>
#include <string>
#include <fstream>
#include "Clock.h"
#include "Config.h"

class interval {
//private members:
private:
	bool verbose;
	Clock* currClock;	
	Clock* alarmClock;
	Config* config;		//struct that interprets config file.
//private methods:
	
//public methods:
public:
	//clock refers to running clock displayed; alarm refers to end point for clock.
	interval(int h=0,int m=0,int s=0,bool editConfig=false,bool verbose=false);
	~interval();
	void print(char clock, bool dispH=false, bool dispM=false, bool Label=true);	//if dispH or dispM is true, following fields will be trunkated
	void printTime(char* argv[], int argc, char field='0', int clockMode=0);
	void printField(char clock, char field);
	std::string getOptionStr(std::string);
	void setAlarm(int h,int m,int s,char dayHalf='0',bool advanceCurrClock=false);
	void runAlarm(bool quiet, bool fullQuiet, bool Hour, bool Min, bool Label=true);
	void countDown(bool quiet, bool fullQuiet, bool Hour,bool Min,bool Label=true);
	void setClock(int h,int m,int s,char dayHalf='0');
	void syncClock();
	int stopwatch(bool quiet, bool fullQuiet, bool Hour,bool Min,bool Label=true);
	void playAlarm() const;
	bool getConfWorldClock() const;
};
