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

printf "\nEvaluating diff -u --color ./bash.out ./minishell.out\n"
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

printf "\nEvaluating diff -u --color ./bash.out ./minishell.out\n"
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

printf "\nEvaluating diff -u --color ./bash.out ./minishell.out\n"
DIFF=$(diff -u --color ./bash.out ./minishell.out)
if [ "$DIFF" ]; then
	printf "\n${RED}Test 3 failed ❌ ⬇️ ${CR}\n"
	diff -u --color ./bash.out ./minishell.out
	echo
else
	printf "\n${GREEN}Test 3 passed ✅${CR}\n\n"
fi

printf "${GREEN}#--------------------------------#${CR}\n"
printf "${GREEN}|        Test 4: unset           |${CR}\n"
printf "${GREEN}#--------------------------------#${CR}\n"

printf "\n./minishell < tests/minishell_test_unset_input_01.sh > minishell.out\n"
printf "bash < tests/minishell_test_unset_input_01.sh > bash.out\n\n"
./minishell < tests/minishell_test_unset_input_01.sh > minishell.out
bash < tests/minishell_test_unset_input_01.sh > bash.out

printf "\nEvaluating diff -u --color ./bash.out ./minishell.out\n"
DIFF=$(diff -u --color ./bash.out ./minishell.out)
if [ "$DIFF" ]; then
	printf "\n${RED}Test 4 failed ❌ ⬇️ ${CR}\n"
	diff -u --color ./bash.out ./minishell.out
	echo
else
	printf "\n${GREEN}Test 4 passed ✅${CR}\n\n"
fi

printf "${GREEN}#--------------------------------#${CR}\n"
printf "${GREEN}|        Test 5: pwd             |${CR}\n"
printf "${GREEN}#--------------------------------#${CR}\n"

printf "\n./minishell < tests/minishell_test_pwd_input_01.sh > minishell.out\n"
printf "bash < tests/minishell_test_pwd_input_01.sh > bash.out\n\n"
./minishell < tests/minishell_test_pwd_input_01.sh > minishell.out
bash < tests/minishell_test_pwd_input_01.sh > bash.out

printf "\nEvaluating diff -u --color ./bash.out ./minishell.out\n"
DIFF=$(diff -u --color ./bash.out ./minishell.out)
if [ "$DIFF" ]; then
	printf "\n${RED}Test 5 failed ❌ ⬇️ ${CR}\n"
	diff -u --color ./bash.out ./minishell.out
	echo
else
	printf "\n${GREEN}Test 5 passed ✅${CR}\n\n"
fi

printf "${GREEN}#--------------------------------#${CR}\n"
printf "${GREEN}|        Test 6: env             |${CR}\n"
printf "${GREEN}#--------------------------------#${CR}\n"

printf "\n./minishell < tests/minishell_test_env_input_01.sh > minishell.out\n"
printf "bash < tests/minishell_test_env_input_01.sh > bash.out\n\n"
./minishell < tests/minishell_test_env_input_01.sh > minishell.out
bash < tests/minishell_test_env_input_01.sh > bash.out

printf "\nEvaluating diff -u --color ./bash.out ./minishell.out\n"
DIFF=$(diff -u --color ./bash.out ./minishell.out)
if [ "$DIFF" ]; then
	printf "\n${RED}Test 6 failed ❌ ⬇️ ${CR}\n"
	diff -u --color ./bash.out ./minishell.out
	echo
else
	printf "\n${GREEN}Test 6 passed ✅${CR}\n\n"
fi

printf "${GREEN}#--------------------------------#${CR}\n"
printf "${GREEN}|        Test 7: exit            |${CR}\n"
printf "${GREEN}#--------------------------------#${CR}\n"

SEQ=`seq -300 300`
echo $SEQ | while read line; do echo "exit $line" | ./minishell; echo $?; done > minishell.out
