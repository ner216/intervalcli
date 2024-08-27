//Notes::
/*
Improve runAlarm function to be more accurate.

*/
#include <iostream>
#include "interval.h"


using namespace std;

interval::interval(int h, int m, int s, bool editConfig, bool verbose){
	//initialize pointer members for composition of structs
	currClock = new Clock();
	alarmClock = new Clock();
	config = new Config();
	this->verbose = verbose;
	/*WHY DOES THIS NOT WORK
	if (config->worldClock == "true"){
		this->worldClock == true;
	}
	*/
	if (editConfig == true){
		system(config->editor.c_str());
	}
	else {
		setClock(h, m, s);
	
		if (verbose == true){
			cout << "[v] -> Running in Verbose Mode [interval::interval]" << endl;
		}
	}
}

interval::~interval(){
	delete this->currClock;
	delete this->alarmClock;
	delete this->config;
	
	if (this->verbose){
		cout << "[v] -> interval pointers deleted [interval::~interval]" << endl;
	}
}

void interval::setClock(int h, int m, int s, char dayHalf){
	if (dayHalf != '0'){
	//configure 12hour clock
	}
	else {
		if (h < 24 && m < 60 && s < 60){
			currClock->hour = h;
			currClock->min = m;
			currClock->sec = s;
			currClock->dayHalf = dayHalf;
			if (this->verbose){
				cout << "[v] -> Clock time set successfully [interval::interval]" << endl;
				cout << "[v] -> Hour: " << h << " Min: " << m << " Sec: " << s << " DayHalf: " << dayHalf << " [interval::setClock]" << endl;
			}
		}
		else {
			cerr << "Error: Invalid time input out of range" << endl;
		}
	}
	
}

void interval::syncClock(char dayHalf){	//make adjustments later for time zone
	struct tm * ptm;
	time_t curTime;
	time_t rawTime;
	time(&curTime); //get time and store it in curTime 	
	time(&rawTime);
	ptm = gmtime(&rawTime);
	
	if (dayHalf == '0'){
		currClock->hour = (ptm->tm_hour + timeMod(config->timeZone)); //uses function from convert library - returns time zone modifier
		if (currClock->hour < 0){
			currClock->hour = currClock->hour + 24;
		}
		currClock->min = ptm->tm_min;
		currClock->sec = ptm->tm_sec;
	}
	
	if (this->verbose){
		cout << "[v] -> Set current clock time [interval::syncClock] ";
		currClock->printTime();
	}
}

void interval::setAlarm(int h, int m, int s, char dayHalf){		//dayHalf can be 'A' or 'P'
	if (config->worldClock == "true"){
		if (h < 24 && m < 60 && s < 60){
			alarmClock->hour = h;
			alarmClock->min = m;
			alarmClock->sec = s;
			alarmClock->dayHalf = dayHalf;
			if (this->verbose){
				cout << "[v] -> Alarm time set successfully [interval::setAlarm]" << endl;
				cout << "[v] -> Hour: " << h << " Min: " << m << " Sec: " << s << " DayHalf: " << dayHalf << " [interval::setAlarm]" << endl;
			}
		}
		else{
			cerr << "Error: invalid input alarm time [interval::setAlarm] [24HOUR]" << endl;
		}
	}
	else {
		if (h < 13 && h > 0 && m < 60 && s < 60){
			alarmClock->hour = h;
			alarmClock->min = m;
			alarmClock->sec = s;
			alarmClock->dayHalf = dayHalf;
			if (this->verbose){
				cout << "[v] -> Alarm time set successfully [interval::setAlarm]" << endl;
				cout << "[v] -> Hour: " << h << " Min: " << m << " Sec: " << s << " DayHalf: " << dayHalf << " [interval::setAlarm]" << endl;
			}
		}
		else{
			cout << "Error: invalid input alarm time [interval::setAlarm] [12HOUR]" << endl;
		}
	}
			
}

void interval::runAlarm(){
	int diffH, diffM, diffS;

	while (true){	
		if (this->verbose == false){
			system("clear");
		}
		cout << "Current ";
		currClock->printTime();
		cout << "Alarm ";
		alarmClock->printTime();
		
		//get difference values by subtracting struct members
		diffH = currClock->hour - alarmClock->hour;
		diffM = currClock->min - alarmClock->min;
		diffS = currClock->sec - alarmClock->sec;
		
		if (diffH == 0){
			if (diffM == 0){
				if (diffS == 0 || diffS == 1){
					cout << "Alarm time reached" << endl;
					playAlarm();
					break;
				}
			}
		}
		syncClock();
		sleep(1);
	}
}


void interval::countDown(bool Hour, bool Min){
	if (this->verbose){
		sleep(3);
	}
	bool alarm = false;

	while (alarm == false){
		currClock->decSec();
		if (*alarmClock == *currClock){
			alarm = true;
			if (this->verbose){
				cout << "[v] -> Alarm time reached [interval::countDown]" << endl;
			}
			cout << "Time complete!" << endl;
			playAlarm();
			break;
		}
		if (this->verbose == false){
			system("clear");
		}
		currClock->printTime(Hour, Min);
		sleep(1.1);
	}
}

void interval::stopwatch(bool Hour, bool Min){
	
	while (true){
		currClock->incSec();
		currClock->printTime(Hour, Min);
		sleep(1.1);
		if (this->verbose == false){
			system("clear");
		}
	}
}



void interval::playAlarm() const{
	system(config->soundDir.c_str());
}
