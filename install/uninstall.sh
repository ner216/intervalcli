#!/bin/bash

read -p "Are you sure you would like to uninstall Interval? (y,N)> " choice

if [ $choice == 'y' ]; then
	read -p "Remove package dependancies [mpg123] (y,N)> " choice
	if [ $choice == 'y' ]; then
		dnf remove mpg123
	fi
	
	echo "Removeing config file..."
	rm /etc/IntervalConfig.conf
	echo "Removeing audio sound effect..."
	rm /usr/share/sounds/alsa/alarm.mp3
	echo "Done"
	
else
	echo "Aborting removal, bye"
fi
