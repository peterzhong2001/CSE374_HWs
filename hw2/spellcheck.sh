#!/bin/bash

# Peter Zhong
# CSE 374 HW2 Q4
# 4/19/2021

# This script checks the spelling of every word in a file against an
# existing dictionary file. It prints out the number of misspelled words
# found in the file and the number of unique words among those misspelled
# words.

filename=$1

# check if correct amount of arguments are received
if [ $# -ne 1 ]
then
    echo 'Error: can only accept one argument' >&2
    exit 1
fi

#check if filename is valid
if [ ! -f $1 ]
then
    echo 'Error: filename not valid' >&2
    exit 1
# check if spelling file already exists
elif [ -f "$filename.spelling" ]
then
    echo "replacing $filename.spelling file" >&1
    rm "$filename.spelling"
fi

count=0
ucount=0

# loop to read lines
while read -ra line
do
    # loop to read words
    for word in "${line[@]}"
    do
	#remove punctuations
	word=$(echo "$word" | tr -d '[:punct:]')
	#remove numbers
	word=$(echo "$word" | tr -d '[:digit:]')
	#remove spaces
	word=$(echo "$word" | tr -d ' ')
	#check if word is empty
	if [ ! -z "$word" ]
	then
	    # set the word to all lower case
	    lowerWord=$(echo "$word" | tr '[:upper:]' '[:lower:]')
	    # get the count of words in the dictionary file
	    instances=$(grep -c "$lowerWord" /usr/share/dict/words)
	    if [[ $instances -eq 0 ]]
	    then
		# check if it is the first iteration
		if [ ! -f "$filename.spelling" ]
		then
		    ucount=$(($ucount + 1))
		    echo "$word" >> "$filename.spelling"
		    count=$(($count + 1))
		else
		    # check if the current word is unique
		    unique=$(grep -c "$word" $filename.spelling)
		    if [[ $unique -eq 0 ]]
		    then
			ucount=$(($ucount + 1))
		    fi
		    # append the word to the spelling file
		    echo "$word" >> "$filename.spelling"
		    count=$(($count + 1))
		fi
	    fi
	fi
    done
done < "$filename"

# print out final messages
echo "found $count spelling errors, output to file $filename.spelling" >&1
echo "$ucount of the words are unique" >&1
exit 0

done
