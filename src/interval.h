#include <iostream>
#include <unistd.h>
#include <time.h>
#include <string>
#include <fstream>
#include "Clock.h"
#include "Config.h"

class interval {
private:
	bool verbose;
	Clock* currClock;	
	Clock* alarmClock;
	Config* config;		//struct that interprets config file.
	
public:
	//clock refers to running clock displayed; alarm refers to end point for clock.
	interval(int h=0,int m=0,int s=0,bool editConfig=false,bool verbose=false);
	~interval();
	std::string getOptionStr(std::string);
	void print(bool=false, bool=false);
	void setAlarm(int,int,int,char='0');
	void runAlarm();
	void countDown(bool h=false,bool m=false);
	void setClock(int,int,int,char='0');
	void syncClock();
	void stopwatch(bool,bool);
	void playAlarm() const;
	bool getConfWorldClock() const;
};
