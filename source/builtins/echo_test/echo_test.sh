#!/bin/bash

OUT=output.txt

echo 'testing zero arguments'
(../echo > zero_arguments.txt)
diff zero_arguments.txt error.txt > output.txt

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm output.txt

echo 'testing one argument'
(../echo hello > one_argument.txt)
diff one_argument.txt 1.txt > output.txt

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm output.txt

echo 'testing two arguments'
(../echo hi again > two_arguments.txt)
diff two_arguments.txt 2.txt > output.txt

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm output.txt

echo 'testing string argument'
(../echo "this works" > string_argument.txt)
diff string_argument.txt str.txt > output.txt

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm output.txt
