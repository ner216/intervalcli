#include <iostream>
#include "interval.h"

void help(){
	cout << "Order of options is not mandatory and not all option fields are required." << endl
	<< "For example; a misc option is not required for usage." << endl
	<< "IMPORTANT: Only one time option can be used at a time." << endl;	
	
	cout << "MonoArgument Commands: " << endl
	<< " [COMMAND] version : version and publish information" << endl
	<< " [COMMAND] help : basic commands and usage" << endl
	<< " [COMMAND] config: edit config file" << endl
	<< " [COMMAND] gui: run application gui" << endl;
	
	cout << "PolyArgument Commands: " << endl;
	cout << "Modes: " << endl;
	cout << " -t : timer" << endl
	<< " -w : stopwatch" << endl
	<< " -a : Alarm" << endl;
	
	cout << "Time Options: " << endl
	<< " -m : minute" << endl
	<< " -s : seconds" << endl
	<< " -h : hours" << endl
	<< " -DM : display values [hours][minutes]" << endl
	<< " -DH : display values [hours]" << endl;
	
	
	cout << "Misc Options: " << endl
	<< " -v : verbose" << endl;
	
	cout << "Usage Examples: " << endl;
	cout << " [COMMAND] -[MODE] -[TIME_OPTION] -[MISC_OPTION] [TIMEVALUE]" << endl
	<< " EX: [COMMAND] -t -m 40" << endl;
}

void errorCodes(){
	cout << "Error Codes:" << endl
	<< "1 : Unable to open configuration file." << endl
	<< "2 : Values in config file are not valid." << endl;
}

void version(){
	cout << "VERSION 1.3.0" << endl
	<< "Date Originally Published: 8-17-24" << endl
	<< "Date of most recent update: 8-26-24" << endl
	<< "Publisher: Nolan Pro" << endl;
}


//argc is length of argv array; 0 is the name of program
//if the program is acompanied by arguments, they are looped through.
//boolean switches are used to store the state of arguments.
int main(int argc, char *argv[]){
	//initialize the variables from config file
	const int TotalConfLines = 8;
	int counter = 0;
	string line;
	string options[] = {"","","",""};

	ifstream config("/etc/IntervalConfig.conf");

	if (config.is_open()){
		for (int i = 0; i < TotalConfLines; i++){
			getline(config, line);
			//use modulus to skip lines that contain labels:
			if (i % 2 != 0){
				options[counter] = line;
				counter++;
			}
		}
	}
	//config variable alias setup:
	string timeZone = options[0];
	string soundDir = options[1];
	string worldClock = options[2];
	string editor = options[3];
	
	//initialize switch variables
	bool editConfig = false;
	bool verbose = false;
	bool timer = false;
	bool alarm = false;
	bool stopwatch = false;
	bool minOP = false;
	bool secOP = false;
	bool hourOP = false;
	bool dispH = false;
	bool dispM = false;
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
				if (argv[i][x] == 'c' && argv[i][x+1] == 'o' && argv[i][x+2] == 'n' && argv[i][x+3] == 'f'){
					editConfig = true;
					break;
				}
				if (argv[i][x] == 'v'){
					verbose = true;
				}
				if (argv[i][x] == 'a'){
					alarm = true;
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
				if (argv[i][x] == 'D' && argv[i][x+1] == 'M'){
					dispM = true;
				}
				if (argv[i][x] == 'D' && argv[i][x+1] == 'H'){
					dispH = true;
				}
				if (ConvertLib::isDigit(argv[i][x]) && secVal == 0 && minVal == 0 && hourVal == 0){
					if (secOP == true){
						secVal = ConvertLib::charToInt(argv[i]);
					}
					else if (minOP == true){
						minVal = ConvertLib::charToInt(argv[i]);
					}
					else if (hourOP == true){
						hourVal = ConvertLib::charToInt(argv[i]);
					}
					else {
						cerr << "Error: Invalid arguments or argument order" << endl;
						return 1;
					}
				}
			}
		//bracket to close for loop
		}
		
		
		//create Clock object using argument values:
		interval clock1 = interval(0, 0, 0, editConfig, verbose);

		
		//check if mode arguments exist.
		
		if (timer == true){
			clock1.setClock(hourVal, minVal, secVal);
			clock1.setAlarm(0,0,0);
			clock1.countDown(dispH, dispM);
		}
		else if (stopwatch == true){
			clock1.setClock(hourVal, minVal, secVal);
			clock1.stopwatch(dispH, dispM);
		}
		else if (alarm == true){
			clock1.syncClock();
			cout << "Enter alarm time(hr min) >";
			cin >> hourVal;
			cin >> minVal;
			if (verbose){
				cout << "HOURVAL: " << hourVal << endl;
				cout << "MINVAL: " << minVal << endl;
			}
			if (hourVal >= 0 && hourVal < 24 && minVal >= 0 && minVal < 60){
				clock1.setAlarm(hourVal,minVal,0);
				clock1.runAlarm();
			}
			else {
				cerr << "Error: invalid input time [main]" << endl;
			}
		}
	
	} //closing bracket for parent if statement
	
	
	return 0;
}
