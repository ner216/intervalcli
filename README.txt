WARNING: THE INSTALLER HAS NOT BEEN FULLY TESTED AND MAY HAVE UNEXPECTED BEHAVIORS! Use at your own risk! The manual install is the safest install method.

Summary:
	Intervalcli is an intuitive alarm, timer, clock, and stopwatch command line application. Created by Nolan Provencher.
	This program comes with no warrenty. Program uses CMAKE, Make, and mpg123. mpg123 is used to create the alarm sound.

How to Get Started:
	
	It is recommended to follow manual install for safety. Bash installer is experimental.
	Installer will install on Debian, Ubuntu, Linux Mint, and Fedora.

	Install with installer script:
		This program includes an install bash script in the 'install' directory. Use this script at your own risk! Installer
		has not been thourghly tested on all systems that are supported. Unexpected behaviors are possible. Also, Installer does not
		check for outside dependancy requirements when it removes them.
		
	Manual Install:
		Install mpg123, CMAKE, Make, g++, and gcc with your package manager.
	
		create a build directory in the src directory. 
		Move to the build directory.
		Run command [cmake ..] to create cmake cache using the parent src directory.
		Run command [cmake --build .] to build the program.
		Copy the 'intervalcli' executable to [/usr/bin/].
		Copy alarm.mp3 to [/usr/share/sounds/alsa/].
		Copy 'IntervalConfig.txt' to [/etc/].
		
		
	To see arguments, 
	enter the command 'interval help'. 
	
Installer Exit Codes:
	1: Script does not have root.
	2: Config file already present and not removed.
	3: Unknown distrobution.
	4: Missing directories of files in package
	5: Could not make directory
	
Intervalcli Exit Codes:
	1: Invalid input time / input time out of range.
	2: Unable to delete config file.
	3: Unable to write to config file.
	5: Clock dayHalf variable is invalid.
	6: Invalid syntax.
	
