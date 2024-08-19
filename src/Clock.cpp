#include <iostream>
#include "Clock.h"
#include <unistd.h>

using namespace std;

Clock::Clock(int h, int m, int s, bool v){
	this->verbose = v;
	
	if (h > 59){
		cout << "Hour out of range: setting to 0" << endl;
		this->hour = 0;
	}
	else {
		this->hour = h;
	}
	if (m > 59){
		cout << "Minute out of range: setting to 0" << endl;
		this->min = 0;
	}
	else {
		this->min = m;
	}
	if (s > 59){
		cout << "Second out of range: setting to 0" << endl;
		this->sec = 0;
	}
	else {
		this->sec = s;
	}
	
	if (this->verbose){
		cout << "[v] -> Clock init Time: " << this->hour << ":" << this->min << ":" << this->sec << endl;
	}

}

void Clock::setClock(int h, int m, int s){
	if (h > 60 || m > 60 | s > 60){
		cout << "Input time has values higher than 60" << endl;
	}
	else {
		this->hour = h;
		this->min = m;
		this->sec = s;
		if (this->verbose){
			cout << "[v] -> Clock set successfully" << endl;
			cout << "[v] -> Clock time: " << this->hour << ":" << this->min << ":" << this->sec << endl;
		}
	}
}

void Clock::setAlarm(int h, int m, int s){
	if (h > 60 || m > 60 | s > 60){
		cout << "Input time has values higher than 60" << endl;
	}
	else {
		this->Ahour = h;
		this->Amin = m;
		this->Asec = s;
		if (this->verbose) {
			cout << "[v] -> Alarm set successfully" << endl;
			cout << "[v] -> Alarm time: " << this->Ahour << ":" << this->Amin << ":" << this->Asec << endl;
		}
	}
}

void Clock::countDown(bool Hour, bool Min){
	bool alarm = false;

	while (alarm == false){
		decSec();
		if (this->hour == this->Ahour && this->min == this->Amin && this->sec == this->Asec){
			alarm = true;
			if (this->verbose){
				cout << "[v] -> Alarm time reached" << endl;
			}
			cout << "Time complete!" << endl;
			playAlarm();
			break;
		}
		system("clear");
		print(Hour, Min);
		sleep(1.1);
	}
}

void Clock::stopwatch(bool Hour, bool Min){
	while (true){
		incSec();
		print(Hour, Min);
		sleep(1.1);
		system("clear");
	}
}

void Clock::print(bool Hour, bool Min){
	if (Min == true){
		cout << "Time -> " << this->hour << ":" << this->min << endl; 
	}
	else if (Hour == true){
		cout << "Time -> " << this->hour << endl;
	}
	else {
		cout << "Time -> " << this->hour << ":" << this->min << ":" << this->sec << endl;
	}
}

void Clock::incSec(){
	this->sec = sec + 1;
	if (this->sec > 59){
		this->sec = 0;
		this->min = min + 1;
		if (this->min > 59){
			this->min = 0;
			this->hour = hour + 1;
		}
	}
}

void Clock::decSec(){
	this->sec = this->sec - 1;
	
	if (this->sec < 1){
		if (this->min > 0){
			this->sec = 59;
			this->min = this->min - 1;
		}
		else {
			if (this->hour > 0){
				this->min = 59;
				this->hour = this->hour - 1;
			}
		}
	}
	
}

void Clock::playAlarm() const{
	system("mpg123 -q /usr/share/sounds/alsa/alarm.mp3");
}
