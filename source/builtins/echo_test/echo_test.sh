#!/bin/bash

OUT=output.txt

echo 'testing zero arguments'
(../echo > zero_arguments.txt)
diff zero_arguments.txt error.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm ${OUT}

echo 'testing one argument'
(../echo hello > one_argument.txt)
diff one_argument.txt 1.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm ${OUT}

echo 'testing two arguments'
(../echo hi again > two_arguments.txt)
diff two_arguments.txt 2.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm ${OUT}

echo 'testing string argument'
(../echo "this works" > string_argument.txt)
diff string_argument.txt str.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm ${OUT}

echo 'testing -n without an argument'
(../echo -n > just_no_nl.txt)
diff just_no_nl.txt no_nl_error.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm ${OUT}

echo 'testing -n with an argument'
(../echo -n hello > no_newline.txt)
diff no_newline.txt no_nl.txt > ${OUT}

if [ ! -s "${OUT}" ]
then
	echo 'OK'
else
	echo 'KO'
fi
rm ${OUT}
