#!/bin/bash

make -C ../../..

STAT=0;
test_list=(
	"bonus_tests.txt"
	"builtin_tests.txt"
	"extras_tests.txt"
	"pipes_tests.txt"
	"redirects_tests.txt"
	"syntax_tests.txt"
	"wildcards_tests.txt"
	)
chmod 000 ./test_files/invalid_permission
mkdir ./outfiles
for testfile in ${test_list[*]}; do
	echo testing $testfile

	while read teste; do
	OUT=$(echo -e "$teste" | ../../../minishell | grep -v '^msh$ ' | grep -v '^exit$')
	# echo "$OUT"
	BASHOUT=$(echo -e "$teste" | bash)
	# echo "$BASHOUT"
	if [ "$OUT" == "$BASHOUT" ]; then
		echo 'OK'
	else
		echo 'KO'
		STAT=1
	fi
	ERR=$(echo -e "$teste" | ../../../minishell 2>&1 > /dev/null)
	echo "$ERR"
	BASHERR=$(echo -e "$teste" | bash 2>&1 > /dev/null)
	echo "$BASHERR"
	if [ -z "$ERR" ]; then
		echo 'OK'
	else
		echo 'KO'
		STAT=1
	fi
	done < $testfile
done

make fclean -C ../../..
chmod 644 ./test_files/invalid_permission
rm -rf ./outfiles

exit $STAT
