#!/bin/bash
srcFile="interval"
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
	
	printf 'Copying files...\n'
	cd ..
	cd src/build/
	sudo cp $srcFile /usr/bin/
	cd ..
	sudo cp $alarmFile /usr/share/sounds/alsa/
	printf 'Successfully copied binary files\n'
	printf 'Installing mpg123...\n'
	sudo dnf install mpg123
	printf 'done\n'
	printf 'Goodbye!\n'
else
	printf 'Unsupported OS\n'
fi


