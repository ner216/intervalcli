#include <iostream>
#include <fstream>
#include "interval.h"

void help(){
	std::cout << "Order of options is not mandatory and not all option fields are required." << std::endl
	<< "For example; a misc option is not required for usage." << std::endl
	<< "IMPORTANT: Only one time option can be used at a time." << std::endl;	
	
	std::cout << "MonoArgument Commands: " << std::endl
	<< " [COMMAND] version : version and publish information" << std::endl
	<< " [COMMAND] help : basic commands and usage" << std::endl
	<< " [COMMAND] config: edit config file" << std::endl
	<< " [COMMAND] repair: regenerate config file" << std::endl
	<< " [COMMAND] codes: list program error codes" << std::endl;
	
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
	<< " -DH : display values [hours]" << std::endl;
	
	
	std::cout << "Misc Options: " << std::endl
	<< " -v : verbose" << std::endl;
	
	std::cout << "Usage Examples: " << std::endl;
	std::cout << " [COMMAND] -[MODE] -[TIME_OPTION] -[MISC_OPTION] [TIMEVALUE]" << std::endl
	<< " EX: [COMMAND] -t -m 40" << std::endl;
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
		exit(3);
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
	std::cout << "VERSION 1.5.1" << std::endl
	<< "Date Originally Published: 8-17-24" << std::endl
	<< "Date of most recent update: 9-1-24" << std::endl
	<< "Publisher: Nolan Pro" << std::endl;
}


//argc is length of argv array; 0 is the name of program
//if the program is acompanied by arguments, they are looped through.
//boolean switches are used to store the state of arguments.
int main(int argc, char *argv[]){
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
				if (argv[i][x] == 'r' && argv[i][x+1] == 'e' && argv[i][x+2] == 'p' && argv[i][x+3] == 'a'){
					repair();
					return 0;
				}
				if (argv[i][x] == 'c' && argv[i][x+1] == 'o' && argv[i][x+2] == 'd' && argv[i][x+3] == 'e'){
					errorCodes();
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
						std::cerr << "Error: Invalid arguments or argument order" << std::endl;
						return 1;
					}
				}
			}
		//bracket to close for loop
		}
		
		
		//create interval object using argument values:
		interval clock = interval(0, 0, 0, editConfig, verbose);

		
		//check if mode arguments exist.
		
		if (timer == true){
			clock.setClock(hourVal, minVal, secVal);
			clock.setAlarm(0,0,0);
			clock.countDown(dispH, dispM);
		}
		else if (stopwatch == true){
			clock.setClock(hourVal, minVal, secVal);
			clock.stopwatch(dispH, dispM);
		}
		else if (alarm == true){
			clock.syncClock();
			std::cout << "Enter alarm time(hr min) >";
			std::cin >> hourVal;
			std::cin >> minVal;
			if (verbose){
				std::cout << "[v] -> HOURVAL: " << hourVal  << " [main]" << std::endl;
				std::cout << "[v] -> MINVAL: " << minVal  << " [main] " << std::endl;
			}
			if (hourVal >= 0 && hourVal < 24 && minVal >= 0 && minVal < 60){
				clock.setAlarm(hourVal,minVal,0);
				clock.runAlarm();
			}
			else {
				std::cerr << "Error: invalid input time [main]" << std::endl;
			}
		}
	
	} //closing bracket for parent if statement
	
	
	return 0;
}
