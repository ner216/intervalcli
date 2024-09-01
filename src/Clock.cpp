#include <iostream>
#include "Clock.h"
	
Clock::Clock(int h, int m, int s, char dayHalf){
	this->hour = h;
	this->min = m;
	this->sec = s;
	this->dayHalf = dayHalf;
}
	
void Clock::printTime(bool h, bool m){
	std::cout << "Time -> ";

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
	
	std::cout << " ";
	
	if (dayHalf != '0'){
		if (dayHalf == 'A'){
			std::cout << "AM";
		}
		if (dayHalf == 'P'){
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

bool Clock::operator==(Clock const& other){
	return (this->hour == other.hour && this->min == other.min && this->sec == other.sec && this->dayHalf == other.dayHalf);
}
	
void Clock::operator=(Clock &other){
	other.hour = this->hour;
	other.min = this->min;
	other.sec = this->sec;
	other.dayHalf = this->dayHalf;
}

double Clock::operator-(Clock const& other){	//needs update for 12 hour clock
	int result;
	int dhour;
	int dmin;
	int dsec;
	
	//abs is absolute value function
	dhour = abs(this->hour - other.hour);	//abs() is from ConvertLib namespace
	dmin = abs(this->min - other.min);
	dsec = abs(this->sec - other.sec);
	
	result = dhour - (dmin / 60) - (dsec / 3600);
	
	//std::cout << "OP -: " << "HOUR: " << dhour << " MIN: " << dmin << " SEC: " << dsec << " RESULT: " << result << std::endl;
	return result;
}



