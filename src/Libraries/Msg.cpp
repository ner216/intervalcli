#include <iostream>
#include "Msg.h"

void Msg::help(){
	std::cout << "NAME" << std::endl;
	std::cout << "	intervalcli - Timer, Alarm, Stopwatch, Clock tool" << std::endl << std::endl;
	std::cout << "SYNOPSIS" << std::endl;
	std::cout << "	intervalcli --[long options] -[options] [single time value]" << std::endl << std::endl;
	std::cout << "DESCRIPTION" << std::endl;
	std::cout << "	The program can run a timer of specified time." << std::endl;
	std::cout << "	The program can set an alarm for a specified time." << std::endl;
	std::cout << "	The program can start a stopwatch from a specified time or from zero." << std::endl << std::endl;
	std::cout << "		MODES:" << std::endl;
	std::cout << "		Timer" << std::endl;
	std::cout << "		Alarm" << std::endl;
	std::cout << "		Stopwatch" << std::endl;
	std::cout << "		Print" << std::endl << std::endl;
	std::cout << "	Different options or long options may be required depending on the mode." << std::endl << std::endl;
	std::cout << "	--help" << std::endl;
	std::cout << "		Return help message showing commands and options" << std::endl << std::endl;
	std::cout << "	--version" << std::endl;
	std::cout << "		Return program version information" << std::endl << std::endl;
	std::cout << "	--config" << std::endl;
	std::cout << "		Launch config editor of program config file (requires root)" << std::endl << std::endl;
	std::cout << "	--repair" << std::endl;
	std::cout << "		Delete and regenerate program config file (requires root)" << std::endl << std::endl;
	std::cout << "	--codes" << std::endl;
	std::cout << "		Return a list of program exit codes" << std::endl << std::endl;
	std::cout << "	--print" << std::endl;
	std::cout << "		Returns system time according to settings in config file. Options can be added to manipulate output as shown:" << std::endl;
	std::cout << "	--[time zone abreviation]" << std::endl;
	std::cout << "		Converts returned time to specified time zone. Ex: PDT, EST, PST..." << std::endl;
	std::cout << "	-[field]" << std::endl;
	std::cout << "		Only returns specified field. field may be 's' for second, 'm' for minute, or 'h' for hour" << std::endl;
	std::cout << "		[time format]" << std::endl;
	std::cout << "		Converts returned time to 12 hour or 24 hour format. This option is not preceded by a '-'." << std::endl;
	std::cout << "		This option can either be entered as '12' or '24'." << std::endl << std::endl;
	std::cout << "	-t" << std::endl;
	std::cout << "		Run interval in timer mode" << std::endl << std::endl;
	std::cout << "	-a" << std::endl;
	std::cout << "		Run interval in alarm mode" << std::endl << std::endl;
	std::cout << "	-w" << std::endl;
	std::cout << "		Run interval in stopwatch mode" << std::endl << std::endl;
	std::cout << "	-m" << std::endl;
	std::cout << "		If used with '--print':" << std::endl;
	std::cout << "			Returns minute value only" << std::endl;
	std::cout << "		Otherwise:" << std::endl;
	std::cout << "			Sets time value to minute value" << std::endl << std::endl;
	std::cout << "	-s" << std::endl;
	std::cout << "		If used with '--print':" << std::endl;
	std::cout << "			Returns second value only" << std::endl;
	std::cout << "		Otherwise:" << std::endl;
	std::cout << "			Sets time value to second value" << std::endl << std::endl;
	std::cout << "	-h" << std::endl;
	std::cout << "		If used with '--print':" << std::endl;
	std::cout << "			Returns hour value only" << std::endl;
	std::cout << "		Otherwise:" << std::endl;
	std::cout << "			Sets time value to hour value" << std::endl << std::endl;
	std::cout << "	-DM" << std::endl;
	std::cout << "		Displays fields up to the minute field, then trunkates the rest." << std::endl << std::endl;
	std::cout << "	-DH" << std::endl;
	std::cout << "		Displays fields up to the hour field, then trunkates the rest." << std::endl << std::endl;
	std::cout << "	-q" << std::endl;
	std::cout << "		Sets interval to quiet output mode. Only outputs 'Timer running...'" << std::endl << std::endl;
	std::cout << "	-FQ" << std::endl;
	std::cout << "		Sets interval to full quiet mode where there is not output to console" << std::endl << std::endl;
	std::cout << "	-v" << std::endl;
	std::cout << "		Sets interval to verbose mode." << std::endl << std::endl;
	std::cout << "	-[single time value]" << std::endl;
	std::cout << "		At the end of a command, a positive integer can be entered as the timer or stopwatch time." << std::endl;
	std::cout << "		This value's repreasentation is determined by '-h', '-m', '-s' options." << std::endl << std::endl;
	std::cout << "USAGE EXAMPLES" << std::endl;
	std::cout << "	Set a timer for 30 minutes:" << std::endl;
	std::cout << "		intervalcli -t -m 30" << std::endl << std::endl;
	std::cout << "	Print time in 12H format:" << std::endl;
	std::cout << "		intervalcli --print 12" << std::endl << std::endl;
	std::cout << "	Print time hour value in 12H format for PDT timezone:" << std::endl;
	std::cout << "		intervalcli --print -h --PDT 12" << std::endl << std::endl;
	std::cout << "	Start stopwatch at 1 hour:" << std::endl;
	std::cout << "		intervalcli -w -h 1" << std::endl << std::endl;
	std::cout << "	Start alarm mode with verbose:" << std::endl;
	std::cout << "		intervalcli -a -v" << std::endl << std::endl;
	std::cout << "AUTHOR" << std::endl;
	std::cout << "	Written by Nolan D. Provencher" << std::endl;
}

void Msg::version(){
	std::cout << "intervalcli 1.9.0" << std::endl
	<< "Date Originally Published: 8-17-24" << std::endl
	<< "Date of most recent update: 9-6-24" << std::endl
	<< "Publisher: Nolan Provencher" << std::endl;
}

void Msg::codes(){
	std::cout << "Error Codes:" << std::endl
	<< "1 : Unable to open configuration file." << std::endl
	<< "2 : Values in config file are not valid." << std::endl
	<< "3 : Unable to modify config file." << std::endl
	<< "4 : Invalid input time." << std::endl;
}
