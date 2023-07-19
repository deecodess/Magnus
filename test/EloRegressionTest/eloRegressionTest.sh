#!/bin/bash

echo "Starting ELO testing script"

##Copying current version to the test folder
cp ../../Magnus MagnusCurrent

if [ ! -f Magnus ]; then

    echo "Magnus not found. Cloning from github and building"

	git clone --depth 1 --branch=master git://github.com/RomainGoussault/Magnus.git LatestRelease/
	cd LatestRelease/
	mkdir obj

	# Get new tags from remote
	git fetch --tags 

	# Get latest tag name
	latestTag=$(git describe --tags `git rev-list --tags --max-count=1`)

	# Checkout latest tag
	git checkout $latestTag

	#Compile it and make it executable
	make Magnus
	chmod +x Magnus

	#Copying latest release version to the test folder
	cp Magnus ../Magnus
	cd ..
fi

./cutechess-cli.sh -engine cmd=MagnusCurrent -engine cmd=Magnus -each proto=uci tc=100/1+0.01 -rounds 700 -pgnout matchOuput.txt -recover -repeat -openings file=openings.pgn | while read line; do

		
	echo "$line"
		
	if [[ "$line" == *ELO*  ]]; then

		#Ouput ELO line
		echo "$line"
	
		minusSign=`echo "$line" | grep -o "-"`

		if [[ $minusSign ]]; then
		
		eloDiff=`echo "$line" | grep -o "[0-9]*"`
		
			if [[ $eloDiff -ge 20 ]]; then #allow up to 20 in Regression
		
				echo "Regression"
				exit 1
			fi
		fi

		echo "No Regression well done"
		exit 0

	fi
done
