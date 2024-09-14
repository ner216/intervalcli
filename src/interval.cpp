#include <iostream>
#include "interval.h"


interval::interval(int h, int m, int s, bool editConfig, bool verbose){
	//initialize pointer members for composition of structs
	this->config = new Config();
	this->currClock = new Clock(this->config->worldClock);
	this->alarmClock = new Clock(this->config->worldClock);
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

void interval::print(char clock, bool dispH, bool dispM, bool Label){
	if (clock == 'c'){
		this->currClock->printTime(dispH, dispM, Label);
	}
	else if (clock == 'a'){
		this->alarmClock->printTime(dispH, dispM, Label);
	}
	else {
		std::cerr << "Error: Invalid values [interval::print]" << std::endl;
		std::exit(1);
	}
}

void interval::printField(char clock, char field){
	if (clock == 'c'){
		switch (field){
			case 'h':
				std::cout << this->currClock->hour << std::endl;
				break;
			case 'm':
				std::cout << this->currClock->min << std::endl;
				break;
			case 's':
				std::cout << this->currClock->sec << std::endl;
				break;
			default:
				std::cerr << "Error: Invalid field [interval::printField]" << std::endl;
		}
	}
	else if (clock == 'a'){
		switch (field){
			case 'h':
				std::cout << this->alarmClock->hour << std::endl;
				break;
			case 'm':
				std::cout << this->alarmClock->min << std::endl;
				break;
			case 's':
				std::cout << this->alarmClock->sec << std::endl;
				break;
			default:
				std::cerr << "Error: Invalid field [interval::printField]" << std::endl;
		}
	}
	else {
		std::cerr << "Error: Invalid clock [interval::printField]" << std::endl;
		exit(1);
	}
}

void interval::printTime(char* argv[], int argc, char field, int clockMode){
	const int ZONELENGTH = 3;
	std::string readZone = "";	
	int timeFormat;
	
	for (int Array = 2; Array < argc; Array++){
		for (int Char = 0; Char < sizeof(argv[Array])/sizeof(char); Char++){
			if (argv[Array][Char] == '-' && argv[Array][Char+1] == '-'){
				if (ConvertLib::isLetter(argv[Array][Char + 2]) == true && Char + 4 < sizeof(argv[Array])/sizeof(char)){
					readZone = readZone + ConvertLib::upper(argv[Array][Char + 2]) + 
						ConvertLib::upper(argv[Array][Char + 3]) + ConvertLib::upper(argv[Array][Char + 4]);
					if (ConvertLib::timeMod(readZone) != 0){
						this->config->timeZone = readZone;
					}
				}
			}
			
		}//closing child for loop
	}//closing parent for loop
	
	if (clockMode == 12){
		this->config->worldClock = "false";
	}
	else if (clockMode == 24){
		this->config->worldClock = "true";
	}
	
	interval::syncClock();
	
	if (field == '0'){
		interval::print('c', false, false, false);	//set disphour and dispmin to false, and label to false
	}
	else if (field == 's' || field == 'h' || field == 'm'){
		interval::printField('c', field);
	}
	else {
		std::cerr << "Error: Invalid field [interval::printTime]" << std::endl;
		std::exit(1);
	}
}

void interval::setClock(int h, int m, int s, char dayHalf){
	if (s > 59){
		m = m + (s / 60);
		s = s % 60;
	}
	if (m > 59){
		h = h + (m / 60);
		m = m % 60;
	}
	
	this->currClock->hour = h;
	this->currClock->min = m;
	this->currClock->sec = s;
	this->currClock->dayHalf = dayHalf;
	if (this->verbose){
		std::cout << "[v] -> Clock time set successfully [interval::interval]" << std::endl;
		std::cout << "[v] -> Hour: " << h << " Min: " << m << " Sec: " << s << " DayHalf: " << dayHalf << " [interval::setClock]" << std::endl;
	}
}

void interval::syncClock(){	//make adjustments later for time zone
	//used by time library to return a time struct:
	struct tm * ptm;
	time_t curTime;
	time_t rawTime;
	time(&curTime); //get time and store it in curTime 	
	time(&rawTime);
	ptm = gmtime(&rawTime);
	
	this->currClock->hour = (ptm->tm_hour + ConvertLib::timeMod(this->config->timeZone)); //uses function from convert library - returns time zone modifier
	
	if (this->currClock->hour < 0){
		this->currClock->hour = this->currClock->hour + 24;
	}
	if (this->config->worldClock == "false"){
		if (this->currClock->hour == 12){
			this->currClock->dayHalf = 'P';
		}
		else if (this->currClock->hour < 12){
			this->currClock->dayHalf = 'A';
		}
		else {
			this->currClock->dayHalf = 'P';
			this->currClock->hour = this->currClock->hour - 12;
		}
	}
	this->currClock->min = ptm->tm_min;
	this->currClock->sec = ptm->tm_sec;

	
	if (this->verbose){
		std::cout << "[v] -> Set current clock time [interval::syncClock] ";
		this->currClock->printTime();
	}
}

void interval::setAlarm(int h, int m, int s, char dayHalf){		//dayHalf can be 'A' or 'P'
	bool validInput = false;	//flag switched when input is validated.
	
	if (this->config->worldClock == "true"){
		if (h < 24 && h >= 0 && m < 60 && m >= 0 && s < 60 && s >= 0){
			validInput = true;
		}
	}
	else {
		if (h <= 12 && h >= 0 && m < 60 && m >= 0 && s < 60 && s >= 0){
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
		std::cerr << "Error [4]: Input time is invalid [interval::setAlarm]" << std::endl;
		std::exit(4);
	}	
}

void interval::runAlarm(bool quiet, bool dispH, bool dispM, bool Label){
	int diffH, diffM, diffS;

	while (true){
		if (quiet == false){
			if (this->verbose == false){
			system("clear");
			}
			std::cout << "Current ";
			interval::print('c', dispH, dispM, Label);
			std::cout << "Alarm ";
			interval::print('a', dispH, dispM, Label);
		}	
		
		//get difference values by subtracting struct members
		diffH = currClock->hour - alarmClock->hour;
		diffM = currClock->min - alarmClock->min;
		diffS = currClock->sec - alarmClock->sec;
		
		if (diffH == 0){
			if (diffM == 0){
				if (diffS == 0 || diffS == 1){
					if (this->currClock->dayHalf == this->alarmClock->dayHalf){
						std::cout << "Alarm time reached" << std::endl;
						playAlarm();
						break;
					}
				}
			}
		}
		interval::syncClock();
		sleep(1);
	}
}


void interval::countDown(bool quiet, bool Hour, bool Min, bool Label){
	if (quiet == false){
		if (this->verbose){
		sleep(3);
	}
	}
	bool alarm = false;

	while (alarm == false){
		if (*alarmClock == *currClock){
			alarm = true;
			if (this->verbose){
				std::cout << "[v] -> Alarm time reached [interval::countDown]" << std::endl;
			}
			std::cout << "Time complete!" << std::endl;
			interval::playAlarm();
			break;
		}

		this->currClock->decSec();

		if (quiet == false){
			if (this->verbose == false){
				std::system("clear");
			}
			interval::print('c', Hour, Min, Label);
		}
		sleep(1.1);
	}
}

void interval::stopwatch(bool quiet, bool Hour, bool Min, bool Label){
	while (true){
		if (quiet == false){
		if (this->verbose == false){
			std::system("clear");
		}
		interval::print('c', Hour, Min, Label);
		}
		this->currClock->incSec();
		sleep(1.1);
	}
}

bool interval::getConfWorldClock() const {
	if (this->config->worldClock == "true"){
		return true;
	}
	else {
		return false;
	}
}

void interval::playAlarm() const{
	std::system(". /usr/bin/SendTimerNotification.sh");
	std::system(config->soundDir.c_str());
}
