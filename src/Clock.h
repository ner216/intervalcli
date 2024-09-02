#include <iostream>
#include <string>

struct Clock {
	int hour;
	int min;
	int sec;
	std::string worldClock;
	char dayHalf;	//dayHalf can be '0' or 'A' or 'P'
	
	Clock(int h, int m, int s, char dayHalf='0');
	Clock(std::string worldClock);
	void printTime(bool h=false, bool m=false);
	void incSec();
	void decSec();
	bool operator==(Clock const& other);
	void operator=(Clock &other);
	double operator-(Clock const& other);
};
