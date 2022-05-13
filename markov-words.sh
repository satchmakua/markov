#!/bin/sh

WORD1="^^^"
WORD2="^^"
WORD3="^"

#Convert all letters to lowercase
#Convert all non-letter characters to newline
#Only print one letter words that contain i,o, or a
tr -c "a-zA-Z" '\n' | tr [:upper:] [:lower:] | \
grep '[a-zA-Z]'| grep -vwE "([b-ef-hj-np-z])" | while read WORD
do
	echo "$WORD1 $WORD2 $WORD3 $WORD"
	WORD1="$WORD2"
	WORD2="$WORD3"
	WORD3="$WORD"
done