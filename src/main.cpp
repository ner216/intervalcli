#include <iostream>
#include <fstream>
#include "interval.h"

void help(){
	std::cout << "Order of options is not enforced and option fields are not all required." << std::endl
	<< "For example; a misc option is not required for usage." << std::endl << std::endl
	<< "IMPORTANT: Only one time option can be used at a time." << std::endl << std::endl;	
	
	std::cout << "MonoArgument Commands: " << std::endl
	<< " --version : version and publish information" << std::endl
	<< " --help : basic commands and usage" << std::endl
	<< " --config: edit config file" << std::endl
	<< " --repair: regenerate config file" << std::endl
	<< " --codes: list program error codes" << std::endl
	<< " --print -[field option] --[timezone] [format option]: returns the current system time." << std::endl
	<< "	-[field opiton]: optional field ex:[h, m, s]" << std::endl
	<< "	-[timezone]: optional timezone convertion ex:[EDT,EST,PDT] See supported timezones in README.md" << std::endl
	<< "	[format option]: optional format specifier: [12,24]. Adding [12] for example will switch the clock to 12 hour time." << std::endl;
	
	std::cout << "PolyArgument Commands: " << std::endl;
	std::cout << "Modes: " << std::endl;
	std::cout << " -t : timer" << std::endl
	<< " -w : stopwatch" << std::endl
	<< " -a : Alarm" << std::endl;
	
	std::cout << "Time Options: " << std::endl
	<< " -m : minute" << std::endl
	<< " -s : seconds" << std::endl
	<< " -h : hours" << std::endl
	<< " -DM : display values [hours][minutes]" << std::endl
	<< " -DH : display values [hours]" << std::endl
	<< " -q : only display label [Timer running...] " << std::endl
	<< " -FQ : show no output to console" << std::endl;
	
	
	std::cout << "Misc Options: " << std::endl
	<< " -v : verbose" << std::endl;
	
	std::cout << "Usage Examples: " << std::endl;
	std::cout << " [COMMAND] -[MODE] -[TIME_OPTION] -[MISC_OPTION] [TIMEVALUE]" << std::endl
	<< " EX: [COMMAND] -t -m 40" << std::endl
	<< " EX: [COMMAND] tm 40" << std::endl
	<< "	sets a timer for 40 minutes" << std::endl
	<< " EX: [COMMAND] print PDT 12" << std::endl
	<< "	returns the time converted to 12h format in the PDT timezone" << std::endl;
}

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

void errorCodes(){
	std::cout << "Error Codes:" << std::endl
	<< "1 : Unable to open configuration file." << std::endl
	<< "2 : Values in config file are not valid." << std::endl
	<< "3 : Unable to modify config file." << std::endl
	<< "4 : Invalid input time." << std::endl;
}

void version(){
	std::cout << "VERSION 1.8.5" << std::endl
	<< "Date Originally Published: 8-17-24" << std::endl
	<< "Date of most recent update: 9-6-24" << std::endl
	<< "Publisher: Nolan Provencher" << std::endl;
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
	
	

	if (argc > 0){
		for (int i = 1; i < argc; i++){
			for (int x = 0; x < sizeof(argv[i])/sizeof(char); x++){
				if (argv[i][x] == '-'){
					while (ConvertLib::isLetter(argv[i][x + opCounter]) == true){
						if (argv[i][x+opCounter] == 'F' && argv[i][x+opCounter+2] == 'Q'){
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
							help();
							return 0;
						}
						else if (argv[i][x+modeCounter] == 'v' && argv[i][x+1+modeCounter] == 'e' && argv[i][x+2+modeCounter] == 'r'){
							version();
							return 0;
						}
						else if (argv[i][x+modeCounter] == 'r' && argv[i][x+1+modeCounter] == 'e' && argv[i][x+2+modeCounter] == 'p' && argv[i][x+3+modeCounter] == 'a'){
							repair();
							return 0;
						}
						else if (argv[i][x+modeCounter] == 'c' && argv[i][x+1+modeCounter] == 'o' && argv[i][x+2+modeCounter] == 'd' && argv[i][x+3+modeCounter] == 'e'){
							errorCodes();
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
				
				if (ConvertLib::isDigit(argv[i][x]) && secVal == 0 && minVal == 0 && hourVal == 0 && clockMode == 0){
					if (secOP == true){
						secVal = ConvertLib::charToInt(argv[i]);
					}
					else if (minOP == true){
						minVal = ConvertLib::charToInt(argv[i]);
					}
					else if (hourOP == true){
						hourVal = ConvertLib::charToInt(argv[i]);
					}
					else if (printTime == true){
						clockMode = ConvertLib::charToInt(argv[i]);
					}
					else {
						std::cerr << "Error: Too many arguments or argument order [main]" << std::endl;
						return 1;
					}
				}	//closing digit if statement
				
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
			clock.setClock(hourVal, minVal, secVal);
			if (quiet == true){
				std::cout << "Timer running..." << std::endl;
			}
			clock.stopwatch(fullQuiet, dispH, dispM);
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
