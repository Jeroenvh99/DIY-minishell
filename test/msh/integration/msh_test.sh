#!/bin/bash

make -C ../../..

test_list=(
	"bonus_tests.txt"
	"builtin_tests.txt"
	"extras_tests.txt"
	"pipes_tests.txt"
	"redirects_tests.txt"
	"syntax_tests.txt"
	"wildcards_tests.txt"
	)
for testfile in ${test_list[*]}; do
	echo testing $testfile

	while read teste; do
		# echo "$teste"
	OUT=$(echo -e "$teste" | ../../../minishell | grep -v '^msh$ ' | grep -v '^exit')
	# echo "$OUT"
	BASHOUT=$(echo -e "$teste" | bash)
	# echo "$BASHOUT"
	if [ "$OUT" == "$BASHOUT" ]; then
		echo 'OK'
	else
		echo 'KO'
	fi
	done < $testfile
done

make fclean -C ../../..