#!/bin/bash

# Peter Zhong
# CSE 374 HW2 Q3
# 4/19/2021

# this script concatenates all the contents from the filenames following
# the first filename. It then uses the first filename to create a new file
# that contains the content of the concatenation.

if [ $# -lt 2 ]
then
    echo 'Error: Less than two arguments passed' >&2
    exit 1
fi

f1=$1
if [ -f "$f1" ]
then
    echo 'Error: first file exists' >&2
    exit 1
fi

shift 1
cat "$@" > "$f1" 2>"$f1"
exit 0
done


