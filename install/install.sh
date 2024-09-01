#!/bin/bash
srcFile="intervalcli"
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
	cd src/
	mkdir build
	cd build/
	#rebuild the project for the system:
	cmake ..
	cmake --build .
	#copy binary to bin:
	cp $srcFile /usr/bin/
	cd ..
	cp $alarmFile /usr/share/sounds/alsa/
	printf 'Successfully copied binary files\n'

	#create config file
	if [ -f $configFile ]; then
		printf "Warning: IntervalConfig.conf present! File must be deleted to continue.\n"
		read -p "Would you like to delete it? (y/N) " choice
		if [ $choice == "y" ]; then
			sudo rm $configFile
		else 
			echo "Config file error: Setup closing"
			exit 2
		fi
	fi
	printf 'Creating Config in /etc/IntervalConfig.conf\n'
	sudo echo "[TimeZone]" >> /etc/IntervalConfig.conf
	sudo echo "EDT" >> /etc/IntervalConfig.conf
	sudo echo "[SoundDir]" >> /etc/IntervalConfig.conf
	sudo echo "/usr/share/sounds/alsa/alarm.mp3" >> /etc/IntervalConfig.conf
	sudo echo "[24HourClock]" >> /etc/IntervalConfig.conf
	sudo echo "true" >> /etc/IntervalConfig.conf
	sudo echo "[Editor]" >> /etc/IntervalConfig.conf
	sudo echo "nano" >> /etc/IntervalConfig.conf
	sudo echo >> /etc/IntervalConfig.conf
	sudo echo >> /etc/IntervalConfig.conf
	sudo echo "#Do not add or remove lines in this file!" >> /etc/IntervalConfig.conf
	sudo echo "#Supported Time Zones: EST, EDT, CST, CDT, MST, MDT, PST, PDT" >> /etc/IntervalConfig.conf
	
	printf 'done\n'
}

installDepDNF(){
	#install dependancies
	printf 'Updating repos...\n'
	dnf update
	printf 'Installing [mpg123,CMAKE,g++,gcc]...\n'
	dnf install mpg123 cmake g++ gcc

}

installDepAPT(){
	printf 'Updating repos...\n'
	apt update
	apt upgrade
	printf 'Installing [mpg123,CMAKE,g++,gcc]...\n'
	apt install mpg123 cmake g++ gcc

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
		read -p "Enter install, cancel, or remove: " choice
		if [ $choice == 'remove' ]; then
			uninstall=true
		elif [ $choice == 'cancel' ]; then
			cancel=true
		elif [ $choice == 'install' ]; then 
			install=true
		else
			cancel=true
		fi
	else
		read -p "Install intervalcli? (y/N)> " choice
		if [ $choice == 'y' ]; then
			install=true
		else
			cancel=true
		fi
	fi
}

#check for install files
printf "Warning: Installer/Uninstaller does not check for dependancy parents or file identity, \ncontinue at your own risk!\n\n"
installCheck

if [ $cancel == true ]; then
	echo "Goodbye!"
	exit 0
fi


if [ $(id -u) == 0 ]; then
	if [ $uninstall == true ]; then
		printf "This action will: \n"
		printf "  Delete mpg123\n  Delete $configFile\n  Delete /usr/share/sounds/alsa/$alarmFile\n  Delete /usr/bin/$srcFile\n"
		read -p "Proceed? (y,N)> " choice
		if [ $choice == 'y' ]; then
			if [ $release == "ID=fedora" ]; then
				dnf remove mpg123
			elif [ $release == "ID=debian" ]||[ $release == "ID=linuxmint" ]||[ $release == "ID=ubuntu" ]; then
				apt remove mpg123
			else
				echo "Error: unknown distrobution! exiting!"
				exit 3
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
		printf "This action will: \n"
		printf "  Install $configFile\n  Install /usr/share/sounds/alsa/$alarmFile\n  Install /usr/bin/$srcFile\n"
		printf "  Install mpg123\n  Install CMAKE\n  Install Make\n  Install g++\n  Install gcc\n"
		read -p "Proceed? (y,N)> " choice
		if [ $choice == 'y' ]; then
			if [ $release == "ID=fedora" ]; then
				installDepDNF
				installBin
			elif [ $release == "ID=debian" ]||[ $release == "ID=linuxmint" ]||[ $release == "ID=ubuntu" ]; then
				installDepAPT
				installBin
			else
				printf 'Unsupported OS\n'
			fi
		fi
	printf 'Goodbye!\n'
	exit 0
	fi
else
	echo "Aborting, Script must be run as root"
	exit 1
fi


