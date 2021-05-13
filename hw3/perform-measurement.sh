#!/bin/bash

# Peter Zhong
# CSE 374 HW3 Q2
# 4/26/2021

# This script takes a url and extracts the byte size of the url.

# check for arguments
if [[ $# -eq 0 ]]
then
    echo 'Error: no argument passed'
    exit 1
fi

# check number of arguments
if [[ $# -ne 1 ]]
then
    echo '0'
    exit 0
fi

# make a temporary file
temp=$(mktemp)

#load url into temp file
wget -o "$temp" "$1" -O /dev/null

# check if successful
failed=$(grep -c 'failed' "$temp")
notFound=$(grep -c '404' "$temp")
if [[ "$failed" -ne 0 ]] | [[ "$notFound" -ne 0 ]]
then
    echo '0'
else
    # filter out the size of the page
    sed -i '/\[[0-9].*]/!d' "$temp"
    sed -i 's/.*\[//g' "$temp"
    sed -i 's/\/.*//g' "$temp"
    sed -i 's/\].*//g' "$temp"
    cat "$temp"
fi

# remove the temporary file
rm "$temp"
exit 0
