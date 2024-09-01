#include <iostream>


using namespace std;

struct Clock {
	int hour;
	int min;
	int sec;
	char dayHalf;	//dayHalf can be '0' or 'A' or 'P'
	
	Clock(int h=0, int m=0, int s=0, char dayHalf='0');
	void printTime(bool h=false, bool m=false);
	void incSec();
	void decSec();
	bool operator==(Clock const& other);
	void operator=(Clock &other);
	double operator-(Clock const& other);
};
