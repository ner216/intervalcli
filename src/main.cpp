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

int* interpretTime(char val[]){
	int count = 0;
	int time[] = {0,0,0};
	int *data = &time[0];
	int h = 0;
	int m = 0;
	int s = 0;

	for (int Char = 0; sizeof(&val)/sizeof(char); Char++){
		if (val[Char] == 'S' && val[Char+1] == 'H' && val[Char+2] == 'E' && val[Char+3] == 'L' && val[Char+4] == 'L'){
			break;
		}
		if (ConvertLib::isDigit(val[Char]) == true && ConvertLib::isDigit(val[Char-1]) == false){
			if (ConvertLib::isDigit(val[Char+1]) == true){
				if (h == 0){
					h = (ConvertLib::charToInt(val[Char]) * 10) + (ConvertLib::charToInt(val[Char+1]));
				}
				else if (h != 0 && m == 0){
					m = (ConvertLib::charToInt(val[Char]) * 10) + (ConvertLib::charToInt(val[Char+1]));
				}
				else if (h != 0 && m != 0 && s == 0){
					s = (ConvertLib::charToInt(val[Char]) * 10) + (ConvertLib::charToInt(val[Char+1]));
				}
				else {
					std::cerr << "Error: Invalid time input for alarm large digit [main::interpretTime]" << std::endl;
				}
			}
			else {
				if (h == 0){
					h = (ConvertLib::charToInt(val[Char]));
				}
				else if (h != 0 && m == 0){
					m = (ConvertLib::charToInt(val[Char]));
				}
				else if (h != 0 && m != 0 && s == 0){
					s = (ConvertLib::charToInt(val[Char]));
				}
				else {
					std::cerr << "Error: Invalid time input for alarm small digit [main::interpretTime]" << std::endl;
				}
			}
		}
	}
	time[0] = h;
	time[1] = m;
	time[2] = s;
	
	return data;
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
	bool hasColon = false;
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
	bool timeSet = false;
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
				
				if (ConvertLib::isDigit(argv[i][x]) == true && ConvertLib::isDigit(argv[i][x-1]) == false && argv[i][x-1] != ':' && timeSet == false){
					if (printTime == true){
						if (argv[i][x] == '1' && argv[i][x+1] == '2'){
							clockMode = 12;
							timeSet = true;
						}
						else if (argv[i][x] == '2' && argv[i][x+1] == '4'){
							clockMode = 24;
							timeSet = true;
						}
					}
					else {
						int* time;
						time = interpretTime(&argv[i][x]);
						if (hourOP == true){
							hourVal = time[0];
							timeSet = true;
						}
						else if (minOP == true){
							minVal = time[0];
							timeSet = true;
						}
						else if (secOP == true){
							secVal = time[0];
							timeSet = true;
						}
						else {
							hourVal = time[0];
							minVal = time[1];
							secVal = time[2];
							timeSet = true;
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
			clock.countDown(quiet, fullQuiet, dispH, dispM);
		}
		else if (stopwatch == true){
			int secondsElapsed = 0;
			clock.setClock(hourVal, minVal, secVal);
			
			//FIX THIS later; find a way to return seconds elapsed when program closes.
			secondsElapsed = clock.stopwatch(quiet, fullQuiet, dispH, dispM);
			
			if (fullQuiet == true){
				std::cout << secondsElapsed << std::endl;
			}
		}
		else if (alarm == true){
			clock.syncClock();
			if (verbose){
				std::cout << "[v] -> HOURVAL: " << hourVal  << " [main]" << std::endl;
				std::cout << "[v] -> MINVAL: " << minVal  << " [main] " << std::endl;
				std::cout << "[v] -> SECVAL: " << secVal << " [main] " << std::endl;
			}
			if (clock.getConfWorldClock() == true){
				if (hourVal >= 0 && hourVal < 24 && minVal >= 0 && minVal < 60){
					clock.setAlarm(hourVal,minVal,secVal,'0');
					clock.runAlarm(quiet, fullQuiet, dispH, dispM);
				}
				else {
					std::cerr << "Error: invalid input time [main]" << std::endl;
					return 1;
				}
			}
			else if (clock.getConfWorldClock() == false){
				if (hourVal > 0 && hourVal <= 12 && minVal >= 0 && minVal < 60){
					clock.setAlarm(hourVal,minVal,secVal,dayHalf);
					clock.runAlarm(quiet, fullQuiet, dispH, dispM);
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
