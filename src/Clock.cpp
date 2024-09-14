#include <iostream>
#include "Clock.h"
	
Clock::Clock(int h, int m, int s, char dayHalf){
	this->hour = h;
	this->min = m;
	this->sec = s;
	this->dayHalf = dayHalf;
}

Clock::Clock(std::string worldClock){
	this->hour = 0;
	this->min = 0;
	this->sec = 0;
	this->worldClock = worldClock;
}
	
void Clock::printTime(bool h, bool m, bool l){
	if (l == true){
		std::cout << "Time -> ";
	}
	if (hour < 10){
		std::cout << "0" << hour;
	}
	else{
		std::cout << hour;
	}
	if (h == false){
		std::cout << ":";
	
		if (min < 10){
			std::cout << "0" << min;
		}
		else{
			std::cout << min;
		}
		

		if (m == false){
			std::cout << ":";
			
			if (sec < 10){
				std::cout << "0" << sec;
			}
			else{
				std::cout << sec;
			}
		}
	}
	
	
	std::cout << " ";
	
	if (this->dayHalf != '0'){
		if (this->dayHalf == 'A'){
			std::cout << "AM";
		}
		if (this->dayHalf == 'P'){
			std::cout << "PM";
		}
	}
	
	std::cout << std::endl;
}

void Clock::incSec(){
	this->sec = sec + 1;
	if (this->sec > 59){
		this->sec = 0;
		this->min = min + 1;
		if (this->min > 59){
			this->min = 0;
			this->hour = hour + 1;
			if (this->worldClock == "true"){
				if (this->hour == 24){
					this->hour = 0;
				}
			}
			else {
				if (this->hour > 12){
					this->hour = 1;
					if (this->dayHalf == 'A'){
						this->dayHalf = 'P';
					}
					else if (this->dayHalf == 'P'){
						this->dayHalf = 'A';
					}
					else {
						std::cerr << "Invalid dayHalf value [Clock::incSec]" << std::endl;
						std::exit(5);
					}
				}
			}
		}
	}
}

void Clock::decSec(){
	this->sec = this->sec - 1;
	
	if (this->sec <= 0){
		if (this->min > 0){
			this->sec = 59;
			this->min = this->min - 1;
		}
		else {
			if (this->hour > 0){
				this->min = 58;
				this->sec = 59;
				this->hour = this->hour - 1;
				if (this->worldClock == "true"){
					if (this->hour < 0){
						this->hour = 24;
					}
				}
				else {
					if (this->hour < 0){
						this->hour = 12;
						if (this->dayHalf == 'A'){
							this->dayHalf = 'P';
						}
						else if (this->dayHalf == 'P'){
							this->dayHalf = 'A';
						}
						else {
							std::cerr << "Invalid dayHalf value [Clock::incSec]" << std::endl;
						}
					}
				}
			}
		}
	}
	
}

bool Clock::operator==(Clock const& other){
	return (this->hour == other.hour && this->min == other.min && this->sec == other.sec && this->dayHalf == other.dayHalf);
}

