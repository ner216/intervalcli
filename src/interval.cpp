#include <iostream>
#include "interval.h"


interval::interval(int h, int m, int s, bool editConfig, bool verbose){
	//initialize pointer members for composition of structs
	this->currClock = new Clock();
	this->alarmClock = new Clock();
	this->config = new Config();
	this->verbose = verbose;
	
	if (editConfig == true){
		std::system(config->editor.c_str());
	}
	else {
		interval::setClock(h, m, s);
	
		if (verbose == true){
			std::cout << "[v] -> Running in Verbose Mode [interval::interval]" << std::endl;
		}
	}
}

interval::~interval(){
	delete this->currClock;
	delete this->alarmClock;
	delete this->config;
	
	if (this->verbose){
		std::cout << "[v] -> interval pointers deleted [interval::~interval]" << std::endl;
	}
}

void interval::setClock(int h, int m, int s, char dayHalf){
	bool validInput = false;	//flag is switched when input is varified

	if (dayHalf != '0'){
		if (h < 13 && h > 0 && m < 60 && m >= 0 && s < 60 && s >= 0){
			validInput = true;
		}
	}
	else {
		if (h < 24 && m < 60 && s < 60){
			validInput = true;
		}
	}
	
	if (validInput == true){
		this->currClock->hour = h;
		this->currClock->min = m;
		this->currClock->sec = s;
		this->currClock->dayHalf = dayHalf;
		if (this->verbose){
			std::cout << "[v] -> Clock time set successfully [interval::interval]" << std::endl;
			std::cout << "[v] -> Hour: " << h << " Min: " << m << " Sec: " << s << " DayHalf: " << dayHalf << " [interval::setClock]" << std::endl;
		}
	}
	else {
		std::cerr << "Error [4]: Input time is invalid" << std::endl;
		std::exit(4);
	}
}

void interval::syncClock(char dayHalf){	//make adjustments later for time zone
	//used by time library to return a time struct:
	struct tm * ptm;
	time_t curTime;
	time_t rawTime;
	time(&curTime); //get time and store it in curTime 	
	time(&rawTime);
	ptm = gmtime(&rawTime);
	
	if (dayHalf == '0'){
		this->currClock->hour = (ptm->tm_hour + ConvertLib::timeMod(config->timeZone)); //uses function from convert library - returns time zone modifier
		if (this->currClock->hour < 0){
			this->currClock->hour = this->currClock->hour + 24;
		}
		this->currClock->min = ptm->tm_min;
		this->currClock->sec = ptm->tm_sec;
	}
	
	if (this->verbose){
		std::cout << "[v] -> Set current clock time [interval::syncClock] ";
		this->currClock->printTime();
	}
}

void interval::setAlarm(int h, int m, int s, char dayHalf){		//dayHalf can be 'A' or 'P'
	bool validInput = false;	//flag switched when input is validated.
	
	if (this->config->worldClock == "true"){
		if (h < 24 && m < 60 && s < 60){
			validInput = true;
		}
	}
	else {
		if (h < 13 && h > 0 && m < 60 && s < 60){
			validInput = true;
		}
	}
	
	if (validInput == true){
		this->alarmClock->hour = h;
		this->alarmClock->min = m;
		this->alarmClock->sec = s;
		this->alarmClock->dayHalf = dayHalf;
		if (this->verbose){
			std::cout << "[v] -> Alarm time set successfully [interval::setAlarm]" << std::endl;
			std::cout << "[v] -> Hour: " << h << " Min: " << m << " Sec: " << s << " DayHalf: " << dayHalf << " [interval::setAlarm]" << std::endl;
		}
	}
	else {
		std::cerr << "Error [4]: Input time is invalid" << std::endl;
		std::exit(4);
	}	
}

void interval::runAlarm(){
	int diffH, diffM, diffS;

	while (true){	
		if (this->verbose == false){
			system("clear");
		}
		std::cout << "Current ";
		currClock->printTime();
		std::cout << "Alarm ";
		alarmClock->printTime();
		
		//get difference values by subtracting struct members
		diffH = currClock->hour - alarmClock->hour;
		diffM = currClock->min - alarmClock->min;
		diffS = currClock->sec - alarmClock->sec;
		
		if (diffH == 0){
			if (diffM == 0){
				if (diffS == 0 || diffS == 1){
					std::cout << "Alarm time reached" << std::endl;
					playAlarm();
					break;
				}
			}
		}
		interval::syncClock();
		sleep(1);
	}
}


void interval::countDown(bool Hour, bool Min){
	if (this->verbose){
		sleep(3);
	}
	bool alarm = false;

	while (alarm == false){
		this->currClock->decSec();
		if (*alarmClock == *currClock){
			alarm = true;
			if (this->verbose){
				std::cout << "[v] -> Alarm time reached [interval::countDown]" << std::endl;
			}
			std::cout << "Time complete!" << std::endl;
			interval::playAlarm();
			break;
		}
		if (this->verbose == false){
			std::system("clear");
		}
		this->currClock->printTime(Hour, Min);
		sleep(1.1);
	}
}

void interval::stopwatch(bool Hour, bool Min){
	while (true){
		this->currClock->incSec();
		this->currClock->printTime(Hour, Min);
		sleep(1.1);
		if (this->verbose == false){
			std::system("clear");
		}
	}
}



void interval::playAlarm() const{
	std::system(config->soundDir.c_str());
}
