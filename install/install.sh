#!/bin/bash
srcFile="interval"
configFile="/etc/IntervalConfig.conf"
alarmFile="alarm.mp3"
#flag variables for installCheck
uninstall=false
cancel=false
install=false
srcPresent=false
configPresent=false
release=$(grep ^ID= /etc/os-release)

installBin(){
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
	#rebuild the project for the system:
	cmake --build .
	#copy binary to bin:
	cp $srcFile /usr/bin/
	cd ..
	cp $alarmFile /usr/share/sounds/alsa/
	printf 'Successfully copied binary files\n'

	#create config file
	if [ -f $configFile ]; then
		read -p "Warning: IntervalConfig.conf present! File must be deleted to continue. Would you like to delete it? (y/N) " choice
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
}

installDepDNF(){
	#install dependancies
	printf 'Updating repos...\n'
	dnf update
	printf 'Installing [mpg123,CMAKE,g++]...\n'
	dnf install mpg123 cmake g++

}

installDepAPT(){
	printf 'Updating repos...\n'
	apt update
	apt upgrade
	printf 'Installing [mpg123,CMAKE,g++]...\n'
	apt install mpg123 cmake g++

}

installCheck(){
	if [ -f /usr/bin/$srcFile ]; then
		srcPresent=true
	fi 
	
	if [ -f $configFile ]; then
		configPresent=true
	fi
	
	if [ $srcPresent == true ]||[ $configPresent == true ]; then
		printf 'Warning: install files already present on system!\nIf this program has not been installed previousely, Cancel install!\n'
		read -p "Enter proceed to install, cancel to exit, remove to uninstall: " choice
		if [ $choice == 'remove' ]; then
			uninstall=true
		elif [ $choice == 'cancel' ]; then
			cancel=true
		elif [ $choice == 'proceed' ]; then 
			install=true
		else
			cancel=true
		fi
	else
		read -p "Install interval with dependancies [mpg123, CMAKE, g++]? (y/N)> " choice
		if [ $choice == 'y' ]; then
			install=true
		else
			cancel=true
		fi
	fi
}

#check for install files
installCheck

if [ $cancel == true ]; then
	echo "Goodbye!"
	exit 0
fi


if [ $USER == "root" ]; then
	if [ $uninstall == true ]; then
		read -p "Remove package dependancies [mpg123] (y,N)> " choice
		if [ $choice == 'y' ]; then
			if [ $release == "ID=fedora" ]; then
				dnf remove mpg123
			elif [ $release == "ID=debian" ]; then
				apt remove mpg123
			else
				echo "Error: unknown distrobution! exiting!"
				exit 1
			fi
		fi
		
		echo "Removeing config file..."
		rm /etc/IntervalConfig.conf
		echo "Removeing audio sound effect..."
		rm /usr/share/sounds/alsa/alarm.mp3
		echo "Removing binaries..."
		rm /usr/bin/$srcFile
		echo "Done"
	elif [ $install == true ]; then
		if [ $release == "ID=fedora" ]; then
			installDepDNF
			installBin
		elif [ $release == "ID=debian"]; then
			installDepAPT
			installBin
		else
			printf 'Unsupported OS\n'
		fi
	printf 'Goodbye!\n'
	exit 0
	fi
else
	echo "Aborting, Script must be run as root"
	exit 1
fi


