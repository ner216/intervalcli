#include <iostream>

using namespace std;

class Clock {
private:
	bool verbose;
	int hour;
	int min;
	int sec;
	int Ahour;
	int Amin;
	int Asec;
public:
	Clock(int=0,int=0,int=0,bool=false);
	//void playAlarm();
	void incSec();
	void decSec();
	void print();
	void setAlarm(int,int,int);
	void countDown();
	void setClock(int,int,int);
	void stopwatch();
};
