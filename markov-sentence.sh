#!/bin/sh

#Run shuffle program to populate SHUF variable
SHUF=$(command -v shuf)
if [ ! -x "$SHUF" ]; then
	if [ -x "./shuffle" ]; then
		SHUF="./shuffle"
	else
		echo "No shuffle program!" 1>& 2
		exit -1
	fi
fi

#Resolve exceptions
if [ $2 -le 0 ];then
	echo "Parameter must be a positive value."
	exit -1
fi

if [ -r "$1" ];then
	echo ""
else
	echo "File not found."
	exit -1
fi

#Get a random line from shuffle 
LINE=$($SHUF < $1 | head -n 1)
#Create four-word fragments
TOTALWORDS=4

#Get words from line by using awk to print them as positonal parameters
WORD1=$(echo $LINE | awk '{print $1}')
WORD2=$(echo $LINE | awk '{print $2}')
WORD3=$(echo $LINE | awk '{print $3}')
WORD4=$(echo $LINE | awk '{print $4}')
#Precede each output line by its relative line number
echo -n "$WORD1 $WORD2 $WORD3 $WORD4 "

#While total words outputed is less than given parameter; continue looping
while [ $TOTALWORDS -lt $2 ]
do
	LINE=$(grep "^$WORD2 $WORD3 $WORD4" $1 | $SHUF | head -n 1)
	WORD1=$(echo $LINE | awk '{print $1}')
	WORD2=$(echo $LINE | awk '{print $2}')
	WORD3=$(echo $LINE | awk '{print $3}')
	WORD4=$(echo $LINE | awk '{print $4}')
	echo -n "$WORD4 "
	TOTALWORDS=$(( $TOTALWORDS + 1 ))
done
