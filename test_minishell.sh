#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
CR="\033[m"

printf "${GREEN}##################################${CR}\n"
printf "${GREEN}#                                #${CR}\n"
printf "${GREEN}#        MINISHELL TESTER        #${CR}\n"
printf "${GREEN}#                                #${CR}\n"
printf "${GREEN}#        Version: 1.0            #${CR}\n"
printf "${GREEN}#        By: jvarila             #${CR}\n"
printf "${GREEN}#                                #${CR}\n"
printf "${GREEN}##################################${CR}\n"
echo

printf "${GREEN}#--------------------------------#${CR}\n"
printf "${GREEN}|        Test 1: echo            |${CR}\n"
printf "${GREEN}#--------------------------------#${CR}\n"

printf "\n./minishell < tests/minishell_test_echo_input_01.sh > minishell.out 2>/dev/null\n"
printf "bash < tests/minishell_test_echo_input_01.sh > bash.out 2>/dev/null\n"
./minishell < tests/minishell_test_echo_input_01.sh > minishell.out 2>/dev/null
bash < tests/minishell_test_echo_input_01.sh > bash.out 2>/dev/null

printf "diff -u --color ./bash.out ./minishell.out\n"
DIFF=$(diff -u --color ./bash.out ./minishell.out)
if [ "$DIFF" ]; then
	printf "\n${RED}Test 1 failed ❌ ⬇️ ${CR}\n"
	diff -u --color ./bash.out ./minishell.out
	echo
else
	printf "\n${GREEN}Test 1 passed ✅${CR}\n\n"
fi

printf "${GREEN}#--------------------------------#${CR}\n"
printf "${GREEN}|        Test 2: export          |${CR}\n"
printf "${GREEN}#--------------------------------#${CR}\n"

printf "\n./minishell < tests/minishell_test_export_input_01.sh > minishell.out 2>/dev/null\n"
printf "bash < tests/minishell_test_export_input_01.sh > bash.out 2>/dev/null\n"
./minishell < tests/minishell_test_export_input_01.sh > minishell.out
bash < tests/minishell_test_export_input_01.sh > bash.out

printf "diff -u --color ./bash.out ./minishell.out\n"
DIFF=$(diff -u --color ./bash.out ./minishell.out)
if [ "$DIFF" ]; then
	printf "\n${RED}Test 2 failed ❌ ⬇️ ${CR}\n"
	diff -u --color ./bash.out ./minishell.out
	echo
else
	printf "\n${GREEN}Test 2 passed ✅${CR}\n\n"
fi

printf "${GREEN}#--------------------------------#${CR}\n"
printf "${GREEN}|        Test 3: cd              |${CR}\n"
printf "${GREEN}#--------------------------------#${CR}\n"

printf "\n./minishell < tests/minishell_test_cd_input_01.sh > minishell.out\n"
printf "bash < tests/minishell_test_cd_input_01.sh > bash.out\n\n"
./minishell < tests/minishell_test_cd_input_01.sh > minishell.out
bash < tests/minishell_test_cd_input_01.sh > bash.out

printf "diff -u --color ./bash.out ./minishell.out\n"
DIFF=$(diff -u --color ./bash.out ./minishell.out)
if [ "$DIFF" ]; then
	printf "\n${RED}Test 2 failed ❌ ⬇️ ${CR}\n"
	diff -u --color ./bash.out ./minishell.out
	echo
else
	printf "\n${GREEN}Test 3 passed ✅${CR}\n\n"
fi
