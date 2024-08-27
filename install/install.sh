#!/bin/bash
srcFile="interval"
configFile="/etc/IntervalConfig.conf"
alarmFile="alarm.mp3"
release=$(grep ^ID= /etc/os-release)

if [ "$release" == "ID=fedora" ]; then
	if [ -f /usr/bin/$srcFile ]; then
		read -p "/usr/bin/$srcFile  found on system; Would you like to delete it before proceeding? (y/N) " choice
		if [ $choice == 'y' ]; then
			printf 'Deleting file...\n'
			sudo rm /usr/bin/$srcFile
			printf 'done\n'
		fi
	fi
	#copy files from download to respective places
	printf 'Copying files...\n'
	cd ..
	cd src/build/
	sudo cp $srcFile /usr/bin/
	cd ..
	sudo cp $alarmFile /usr/share/sounds/alsa/
	printf 'Successfully copied binary files\n'
	#install dependancies
	printf 'Installing mpg123...\n'
	sudo dnf install mpg123
	#create config file
	if [ -f "$configFile" ]; then
		read -p "Warning: IntervalConfig.conf present, would you like to delete it (y/N) " choice
		if [ $choice == "y" ]; then
			sudo rm $configFile
		else 
			echo "Config file error: Setup closing"
			exit 1
		fi
	fi
	
	printf 'Creating Config in /etc/IntervalConfig.conf\n'
	sudo echo "[TimeZone]" >> /etc/IntervalConfig.conf
	sudo echo "EST" >> /etc/IntervalConfig.conf
	sudo echo "[SoundDir]" >> /etc/IntervalConfig.conf
	sudo echo "/usr/share/sounds/alsa/alarm.mp3" >> /etc/IntervalConfig.conf
	sudo echo "[24HourClock]" >> /etc/IntervalConfig.conf
	sudo echo "true" >> /etc/IntervalConfig.conf
	sudo echo "[Editor]" >> /etc/IntervalConfig.conf
	sudo echo "nano" >> /etc/IntervalConfig.conf
	
	printf 'done\n'
	printf 'Goodbye!\n'
else
	printf 'Unsupported OS\n'
fi


