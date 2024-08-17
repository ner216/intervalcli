#include <iostream>
#include "Clock.h"

void help(){
	cout << "Order of options is not mandatory and not all option fields are required." << endl
	<< "For example; a misc option is not required for usage." << endl
	<< "IMPORTANT: Only one time option can be used at a time." << endl;	
	
	cout << "MonoArgument Commands: " << endl
	<< " [COMMAND] version : version and publish information" << endl
	<< " [COMMAND] help : basic commands and usage" << endl;
	
	cout << "Modes: " << endl;
	cout << " -t : timer" << endl
	<< " -w : stopwatch" << endl;
	
	cout << "Time Options: " << endl
	<< " -m : minute" << endl
	<< " -s : seconds" << endl
	<< " -h : hours" << endl;
	
	cout << "Misc Options: " << endl
	<< " -v : verbose" << endl;
	
	cout << "Usage Examples: " << endl;
	cout << " [COMMAND] -[MODE] -[TIME_OPTION] -[MISC_OPTION] [TIMEVALUE]" << endl
	<< " EX: [COMMAND] -t -m 40" << endl;
}

void version(){
	cout << "VERSION 1.0.0" << endl
	<< "Date Published: 8-17-24" << endl
	<< "Publisher: Nolan Pro" << endl;
}

bool isDigit(char val){
	char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	for (int i = 0; i < 10; i++){
		if (digits[i] == val){
			return true;
		}
	}
	
	return false;
}

int powTen(int n){
	int result = 1;
	
	for (int i = 0; i < n; i++){
		result = result * 10;
	}
	
	return result;
}

int charToInt(char val[]){
	char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	int result = 0;	
	int power = 0;
	
	for (int i = sizeof(&val)/sizeof(char); i >= 0 ; i--){
		for (int y = 0; y < 10; y++){
			if (val[i] == digits[y]){
				result = result + (y * powTen(power));
				power++;
			}
		}
	}
	
	return result;
}

//argc is length of argv array; 0 is the name of program
//if the program is acompanied by arguments, they are looped through.
//boolean switches are used to store the state of arguments.
int main(int argc, char *argv[]){
	bool verbose = false;
	bool timer = false;
	bool stopwatch = false;
	bool minOP = false;
	bool secOP = false;
	bool hourOP = false;
	int minVal = 0;
	int secVal = 0;
	int hourVal = 0;
	

	if (argc > 0){
		for (int i = 1; i < argc; i++){
			for (int x = 0; x < sizeof(argv[i])/sizeof(char); x++){
				if (argv[i][x] == 'h' && argv[i][x+1] == 'e'){
					help();
					return 0;
				}
				if (argv[i][x] == 'v' && argv[i][x+1] == 'e' && argv[i][x+2] == 'r'){
					version();
					return 0;
				}
				if (argv[i][x] == 'v'){
					verbose = true;
				}
				if (argv[i][x] == 'w'){
					stopwatch = true;
				}
				if (argv[i][x] == 't'){
					timer = true;
				}
				if (argv[i][x] == 'm'){
					minOP = true;
				}
				if (argv[i][x] == 's'){
					secOP = true;
				}
				if (argv[i][x] == 'h'){
					hourOP = true;
				}
				if (isDigit(argv[i][x]) && secVal == 0 && minVal == 0 && hourVal == 0){
					if (secOP == true){
						secVal = charToInt(argv[i]);
					}
					else if (minOP == true){
						minVal = charToInt(argv[i]);
					}
					else if (hourOP == true){
						hourVal = charToInt(argv[i]);
					}
					else {
						cout << "Error: Invalid arguments or argument order" << endl;
						return 1;
					}
				}
			}
		//bracket to close for loop
		}
		
		//create Clock object using argument values:
		Clock clock1 = Clock(hourVal, minVal, secVal, verbose);
		//check if mode arguments exist.
		if (timer == true){
			clock1.setAlarm(0,0,0);
			clock1.countDown();
		}
		if (stopwatch == true){
			clock1.stopwatch();
		}
	
	} //closing bracket for parent if statement
	
	
	return 0;
}
