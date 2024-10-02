#include <iostream>
#include <fstream>
#include "interval.h"
#include "Libraries/Msg.h"

void repair(){
        std::string config = "/etc/IntervalConfig.conf";
        //delete config file:
	try {
		if (std::filesystem::remove(config)){
			std::cout << "Old config file successfully deleted" << std::endl;
		}
	}
	catch (std::filesystem::__cxx11::filesystem_error) {
		std::cerr << "Error: Old config file could not be deleted! run as root?" << std::endl;
		exit(2);
	}
	
	
	//create and write data to new config file:
	std::ofstream newConf(config);
	if (newConf.is_open()){
		newConf << "[TimeZone]" << std::endl;
		newConf << "EDT" << std::endl;
		newConf << "[SoundDir]" << std::endl;
		newConf << "/usr/share/sounds/alsa/alarm.mp3" << std::endl;
		newConf << "[24HourClock]" << std::endl;
		newConf << "true" << std::endl;
		newConf << "[Editor]" << std::endl;
		newConf << "nano" << std::endl;
		
		newConf << std::endl << std::endl;
		newConf << "#Do not add or remove lines in this file!" << std::endl;
		newConf << "#Supported Time Zones: EST, EDT, CST, CDT, MST, MDT, PST, PDT" << std::endl;
		
		std::cout << "New Config file successfully populated" << std::endl;
	}
	else {
		std::cerr << "Error: unable to write to config file [repair]" << std::endl;
		std::exit(3);
	}
	
	newConf.close();
	
}

void printCommand(int argc, char *argv[]){
	for (int Array = 0; Array < argc; Array++){
		for (int Char = 0; Char < sizeof(*argv)/sizeof(char); Char++){
			std::cout << argv[Array][Char];
		}
		std::cout << std::endl;
	}

}

void checkSyntax(int argc, char *argv[]){
	const char shellText[5] = {'S', 'H', 'E', 'L', 'L'};
	int shellTextIdx[5];
	bool shellFlags[5] = {false, false, false, false, false};
	bool verbose = false;
	bool ifSHELL = false;
	bool longOption = false;
	bool badOption = false;		
	bool badLongOption = false;	
	int counter = 0;

	for (int Array = 1; Array < argc; Array++){
		for (int Char = 0; Char < sizeof(argv[Array])/sizeof(char); Char++){
			if (argv[Array][Char] == 'S' && argv[Array][Char+1] == 'H' && argv[Array][Char+2] == 'E' && argv[Array][Char+3] == 'L' && argv[Array][Char+4] == 'L'){
				break;
			}
			if (ConvertLib::isLetter(argv[Array][Char]) == true){
				if (ConvertLib::lower(argv[Array][Char]) == 'p' && ConvertLib::lower(argv[Array][Char+1]) == 'r' && ConvertLib::lower(argv[Array][Char+2]) == 'i' && ConvertLib::lower(argv[Array][Char+3]) == 'n' && ConvertLib::lower(argv[Array][Char+4]) == 't'){
					longOption = true;
				}
				if (ConvertLib::lower(argv[Array][Char]) == 'c' && ConvertLib::lower(argv[Array][Char+1]) == 'o' && ConvertLib::lower(argv[Array][Char+2]) == 'n' && ConvertLib::lower(argv[Array][Char+3]) == 'f' && ConvertLib::lower(argv[Array][Char+4]) == 'i'){
					longOption = true;
				}
				if (ConvertLib::lower(argv[Array][Char]) == 'r' && ConvertLib::lower(argv[Array][Char+1]) == 'e' && ConvertLib::lower(argv[Array][Char+2]) == 'p' && ConvertLib::lower(argv[Array][Char+3]) == 'a' && ConvertLib::lower(argv[Array][Char+4]) == 'i'){
					longOption = true;
				}
				if (ConvertLib::lower(argv[Array][Char]) == 'c' && ConvertLib::lower(argv[Array][Char+1]) == 'o' && ConvertLib::lower(argv[Array][Char+2]) == 'd' && ConvertLib::lower(argv[Array][Char+3]) == 'e'){
					longOption = true;
				}
				if (ConvertLib::lower(argv[Array][Char]) == 'v' && ConvertLib::lower(argv[Array][Char+1]) == 'e' && ConvertLib::lower(argv[Array][Char+2]) == 'r' && ConvertLib::lower(argv[Array][Char+3]) == 's' && ConvertLib::lower(argv[Array][Char+4]) == 'i'){
					longOption = true;
				}
				if (ConvertLib::lower(argv[Array][Char]) == 'h' && ConvertLib::lower(argv[Array][Char+1]) == 'e' && ConvertLib::lower(argv[Array][Char+2]) == 'l' && ConvertLib::lower(argv[Array][Char+3]) == 'p'){
					longOption = true;
				}
					
				if (longOption == true){
					if (ConvertLib::isLetter(argv[Array][Char-1]) != false || argv[Array][Char-1] != '-' || argv[Array][Char-2] != '-'){
						badLongOption = true;
					}
				}

				else if(longOption == false){
					if (ConvertLib::isLetter(argv[Array][Char-1]) == false && argv[Array][Char-1] != '-'){
						badOption = true;
					}
				}
				longOption = false;
				counter = 0;
			}
		}//close child for loop
	}//close parent for loop
	
	if (badOption == true){
		std::cerr << "Syntax Error: options missing '-' ?" << std::endl;
		std::exit(6);
	}
	if (badLongOption == true){
		std::cerr << "Syntax Error: options missing '--' ?" << std::endl;
		std::exit(6);
	}
}


//argc is length of argv array; 0 is the name of program
//if the program is acompanied by arguments, they are looped through.
//boolean switches are used to store the state of arguments.
int main(int argc, char *argv[]){
	//counter variables for parsing argv array:
	int opCounter = 1;
	int modeCounter = 2;
	//initialize switch variables:
	bool quiet = false;
	bool fullQuiet = false;
	bool printTime = false;
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
	//clock value variables:
	int clockMode = 0;		//stores 12h or 24h
	int minVal = 0;
	int secVal = 0;
	int hourVal = 0;
	//Variables for mode functions:
	std::string dayHalfSTR;
	char field = '0';	//used for print option
	char dayHalf;		//am or pm
	//Used to modify timezone for main print option.
	int worldClock = true;
	
	//FOR DEBUGGING:
	//printCommand(argc,argv);
	//syntax check:
	checkSyntax(argc,argv);
	//set option flags:
	if (argc > 0){
		for (int i = 1; i < argc; i++){
			for (int x = 0; x < sizeof(argv[i])/sizeof(char); x++){
				if (argv[i][x] == '-' && argv[i][x+1] != '-' && argv[i][x-1] != '-'){
					while (ConvertLib::isLetter(argv[i][x + opCounter]) == true){
						if (argv[i][x+opCounter] == 'F' && argv[i][x+opCounter+1] == 'Q'){
							fullQuiet = true;
						}
						if (argv[i][x+opCounter] == 'D' && argv[i][x+opCounter+1] == 'H'){
							dispH = true;
						}
						
						if (argv[i][x + opCounter] == 'q'){
							fullQuiet = true;
							quiet = true;
						}
						else if (argv[i][x + opCounter] == 'v'){
							verbose = true;
						}
						else if (argv[i][x + opCounter] == 'a'){
							alarm = true;
						}
						else if (argv[i][x + opCounter] == 'w'){
							stopwatch = true;
						}
						else if (argv[i][x + opCounter] == 't'){
							timer = true;
						}
						else if (argv[i][x + opCounter] == 'm'){
							minOP = true;
						}
						else if (argv[i][x + opCounter] == 's'){
							secOP = true;
						}
						else if (argv[i][x + opCounter] == 'h'){
							hourOP = true;
						}
						else if (argv[i][x + opCounter] == 'D' && argv[i][x+1+opCounter] == 'M'){
							dispM = true;
						}
						
						opCounter++;
					}
					
					opCounter = 1;
				}	//closing option if statement
				
				if (argv[i][x] == '-' && argv[i][x+1] == '-'){
					while (ConvertLib::isLetter(argv[i][x + modeCounter]) == true){
						if (argv[i][x + modeCounter] == 'h' && argv[i][x + 1 + modeCounter] == 'e'){
							Msg::help();
							return 0;
						}
						else if (argv[i][x+modeCounter] == 'v' && argv[i][x+1+modeCounter] == 'e' && argv[i][x+2+modeCounter] == 'r'){
							Msg::version();
							return 0;
						}
						else if (argv[i][x+modeCounter] == 'r' && argv[i][x+1+modeCounter] == 'e' && argv[i][x+2+modeCounter] == 'p' && argv[i][x+3+modeCounter] == 'a'){
							repair();
							return 0;
						}
						else if (argv[i][x+modeCounter] == 'c' && argv[i][x+1+modeCounter] == 'o' && argv[i][x+2+modeCounter] == 'd' && argv[i][x+3+modeCounter] == 'e'){
							Msg::codes();
							return 0;
						}
						else if (argv[i][x+modeCounter] == 'c' && argv[i][x+1+modeCounter] == 'o' && argv[i][x+2+modeCounter] == 'n' && argv[i][x+3+modeCounter] == 'f'){
							editConfig = true;
						}
						else if (argv[i][x+modeCounter] == 'p' && argv[i][x+1+modeCounter] == 'r' && argv[i][x+2+modeCounter] == 'i'){
							printTime = true;
						}
					
					modeCounter++;
					}
				modeCounter = 2;
				}	//closing mod if statement
				
				if (ConvertLib::isDigit(argv[i][x]) == true){
					if (printTime == true){
						if (clockMode == 0){
							clockMode = ConvertLib::charToInt(argv[i]);
						}
					}
					else {
						if (secVal == 0 && minVal == 0 && hourVal == 0){
							if (secOP == true){
								secVal = ConvertLib::charToInt(argv[i]);
							}
							else if (minOP == true){
								minVal = ConvertLib::charToInt(argv[i]);
							}
							else if (hourOP == true){
								hourVal = ConvertLib::charToInt(argv[i]);
							}
						}
					}
				}//close isdigit if statement
			
			}//bracket to close child for loop
		}//bracket to close parent for loop
		
		//create interval object using argument values:
		interval clock = interval(0, 0, 0, editConfig, verbose);

		
		//check if mode arguments exist.
		if (printTime == true){
			if (hourOP == true){
				field = 'h';
			}
			if (minOP == true){
				field = 'm';
			}
			if (secOP == true){
				field = 's';
			}
			clock.printTime(argv, argc, field, clockMode);
			return 0;
		}
		
		if (timer == true){
			clock.setClock(hourVal, minVal, secVal);
			clock.setAlarm(0,0,0);
			if (quiet == true){
				std::cout << "Timer running..." << std::endl;
			}
			clock.countDown(fullQuiet, dispH, dispM);
		}
		else if (stopwatch == true){
			int secondsElapsed = 0;
			clock.setClock(hourVal, minVal, secVal);
			
			if (quiet == true){
				std::cout << "Timer running..." << std::endl;
			}
			//FIX THIS later; find a way to return seconds elapsed when program closes.
			secondsElapsed = clock.stopwatch(fullQuiet, dispH, dispM);
			
			if (fullQuiet == true){
				std::cout << secondsElapsed << std::endl;
			}
		}
		else if (alarm == true){
			clock.syncClock();
			std::cout << "Enter alarm time(hr min) >";
			std::cin >> hourVal;
			std::cin >> minVal;
			if (clock.getConfWorldClock() == false){
				std::cout << "AM or PM: ";
				std::cin >> dayHalfSTR;
				if (dayHalfSTR == "AM" || dayHalfSTR == "am" || dayHalfSTR == "a" || dayHalfSTR == "A"){
					dayHalf = 'A';
				}
				else if (dayHalfSTR == "PM" || dayHalfSTR == "pm" || dayHalfSTR == "p" || dayHalfSTR == "P"){
					dayHalf = 'P';
				}
				else {
					std::cerr << "Error: invalid input for dayHalf [main]" << std::endl;
					return 1;
				}
			}
			if (verbose){
				std::cout << "[v] -> HOURVAL: " << hourVal  << " [main]" << std::endl;
				std::cout << "[v] -> MINVAL: " << minVal  << " [main] " << std::endl;
			}
			if (clock.getConfWorldClock() == true){
				if (hourVal >= 0 && hourVal < 24 && minVal >= 0 && minVal < 60){
					clock.setAlarm(hourVal,minVal,secVal,'0');
					if (quiet == true){
						std::cout << "Timer running..." << std::endl;
					}
					clock.runAlarm(fullQuiet, dispH, dispM);
				}
				else {
					std::cerr << "Error: invalid input time [main]" << std::endl;
					return 1;
				}
			}
			else if (clock.getConfWorldClock() == false){
				if (hourVal > 0 && hourVal <= 12 && minVal >= 0 && minVal < 60){
					clock.setAlarm(hourVal,minVal,secVal,dayHalf);
					if (quiet == true){
						std::cout << "Timer running..." << std::endl;
					}
					clock.runAlarm(fullQuiet, dispH, dispM);
				}
				else {
					std::cerr << "Error: invalid input time [main]" << std::endl;
					return 1;
				}
			}
			
		}
	
	} //closing bracket for parent if statement
	
	
	return 0;
}
