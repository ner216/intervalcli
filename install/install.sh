#!/bin/bash
srcFile="interval"
release=$(grep ^ID= /etc/os-release)

if [ "$release" == "ID=fedora" ]; then
	if [ -f /usr/bin/$srcFile ]; then
		read -p "/usr/bin/$srcFile  found on system; Would you like to delete it before proceeding? (y/N)" choice
		if [ $choice == 'y' ]; then
			printf 'Deleting file...\n'
			sudo rm /usr/bin/$srcFile
			printf 'done\n'
		fi
	fi
	
	printf 'Copying binary files...\n'
	cd ..
	cd src/build/
	sudo cp $srcFile /usr/bin/
	printf 'Successfully copied binary files\n'
	printf 'Goodbye!\n'
else
	printf 'Unsupported OS\n'
fi


