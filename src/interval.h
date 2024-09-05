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
	std::string getOptionStr(std::string);
	void setAlarm(int h,int m,int s,char dayHalf='0');
	void runAlarm(bool quiet, bool Hour, bool Min, bool Label=true);
	void countDown(bool quiet, bool Hour,bool Min,bool Label=true);
	void setClock(int h,int m,int s,char dayHalf='0');
	void syncClock(bool wc=0, std::string zone="none");
	void stopwatch(bool quiet, bool Hour,bool Min,bool Label=true);
	void playAlarm() const;
	bool getConfWorldClock() const;
};
