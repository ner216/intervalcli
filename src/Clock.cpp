/*NOTES:
remove/fix overload operators

*/
#include <iostream>
#include "Clock.h"
using namespace std;
	
Clock::Clock(int h, int m, int s, char dayHalf){
	this->hour = h;
	this->min = m;
	this->sec = s;
	this->dayHalf = dayHalf;
}
	
void Clock::printTime(bool h, bool m){
	cout << "Time -> ";

	if (hour < 10){
		cout << "0" << hour;
	}
	else{
		cout << hour;
	}
	
	if (h == false){
		cout << ":";
		
		if (min < 10){
			cout << "0" << min;
		}
		else{
			cout << min;
		}
	}
	
	if (m == false){
		cout << ":";
		
		if (sec < 10){
			cout << "0" << sec;
		}
		else{
			cout << sec;
		}
	}
	
	cout << " ";
	
	if (dayHalf != '0'){
		if (dayHalf == 'A'){
			cout << "AM";
		}
		if (dayHalf == 'P'){
			cout << "PM";
		}
	}
	
	cout << endl;
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
	dhour = abs(this->hour - other.hour);
	dmin = abs(this->min - other.min);
	dsec = abs(this->sec - other.sec);
	
	result = dhour - (dmin / 60) - (dsec / 3600);
	
	//cout << "OP -: " << "HOUR: " << dhour << " MIN: " << dmin << " SEC: " << dsec << " RESULT: " << result << endl;
	return result;
}



