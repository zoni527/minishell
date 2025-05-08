#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
CR="\033[m"

MINIDIR="$HOME/Repos/minishell"
MINISHELL="$MINIDIR/minishell"
TESTDIR="$MINIDIR/tests"
MINIOUT=$TESTDIR/minishell.out
BASHOUT=$TESTDIR/bash.out

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

printf "\n../minishell < minishell_test_echo_input_01.sh > $MINIOUT 2>/dev/null\n"
printf "bash < minishell_test_echo_input_01.sh > bash.out 2>/dev/null\n"
$MINISHELL < $TESTDIR/minishell_test_echo_input_01.sh > $MINIOUT 2>/dev/null
bash < $TESTDIR/minishell_test_echo_input_01.sh > $BASHOUT 2>/dev/null

printf "\nEvaluating diff -u --color bash.out minishell.out\n"
DIFF=$(diff -u --color $BASHOUT $MINIOUT)
if [ "$DIFF" ]; then
	printf "\n${RED}Test 1 failed ❌ ⬇️ ${CR}\n"
	diff -u --color $BASHOUT $MINIOUT
	echo
else
	printf "\n${GREEN}Test 1 passed ✅${CR}\n\n"
fi

printf "${GREEN}#--------------------------------#${CR}\n"
printf "${GREEN}|        Test 2: export          |${CR}\n"
printf "${GREEN}#--------------------------------#${CR}\n"

printf "\n../minishell < minishell_test_export_input_01.sh > minishell.out 2>/dev/null\n"
printf "bash < minishell_test_export_input_01.sh > bash.out 2>/dev/null\n\n"

$MINISHELL < $TESTDIR/minishell_test_export_input_01.sh > $MINIOUT
bash < $TESTDIR/minishell_test_export_input_01.sh > $BASHOUT

printf "\nEvaluating diff -u --color bash.out minishell.out\n"
DIFF=$(diff -u --color $BASHOUT $MINIOUT)
if [ "$DIFF" ]; then
	printf "\n${RED}Test 2 failed ❌ ⬇️ ${CR}\n"
	diff -u --color $BASHOUT $MINIOUT
	echo
else
	printf "\n${GREEN}Test 2 passed ✅${CR}\n\n"
fi

printf "${GREEN}#--------------------------------#${CR}\n"
printf "${GREEN}|        Test 3: cd              |${CR}\n"
printf "${GREEN}#--------------------------------#${CR}\n"

printf "\n../minishell < minishell_test_cd_input_01.sh > minishell.out\n"
printf "bash < minishell_test_cd_input_01.sh > bash.out\n\n"
$MINISHELL < $TESTDIR/minishell_test_cd_input_01.sh > $MINIOUT
bash < $TESTDIR/minishell_test_cd_input_01.sh > $BASHOUT

printf "\nEvaluating diff -u --color bash.out minishell.out\n"
DIFF=$(diff -u --color $BASHOUT $MINIOUT)
if [ "$DIFF" ]; then
	printf "\n${RED}Test 3 failed ❌ ⬇️ ${CR}\n"
	diff -u --color $BASHOUT $MINIOUT
	echo
else
	printf "\n${GREEN}Test 3 passed ✅${CR}\n\n"
fi

printf "${GREEN}#--------------------------------#${CR}\n"
printf "${GREEN}|        Test 4: unset           |${CR}\n"
printf "${GREEN}#--------------------------------#${CR}\n"

printf "\n../minishell < minishell_test_unset_input_01.sh > minishell.out\n"
printf "bash < minishell_test_unset_input_01.sh > bash.out\n\n"
$MINISHELL < $TESTDIR/minishell_test_unset_input_01.sh > $MINIOUT
bash < $TESTDIR/minishell_test_unset_input_01.sh > $BASHOUT

printf "\nEvaluating diff -u --color bash.out minishell.out\n"
DIFF=$(diff -u --color $BASHOUT $MINIOUT)
if [ "$DIFF" ]; then
	printf "\n${RED}Test 4 failed ❌ ⬇️ ${CR}\n"
	diff -u --color $BASHOUT $MINIOUT
	echo
else
	printf "\n${GREEN}Test 4 passed ✅${CR}\n\n"
fi

printf "${GREEN}#--------------------------------#${CR}\n"
printf "${GREEN}|        Test 5: pwd             |${CR}\n"
printf "${GREEN}#--------------------------------#${CR}\n"

printf "\n../minishell < minishell_test_pwd_input_01.sh > minishell.out\n"
printf "bash < minishell_test_pwd_input_01.sh > bash.out\n\n"
$MINISHELL < $TESTDIR/minishell_test_pwd_input_01.sh > $MINIOUT
bash < $TESTDIR/minishell_test_pwd_input_01.sh > $BASHOUT

printf "\nEvaluating diff -u --color $BASHOUT $MINIOUT"
DIFF=$(diff -u --color $BASHOUT $MINIOUT)
if [ "$DIFF" ]; then
	printf "\n${RED}Test 5 failed ❌ ⬇️ ${CR}\n"
	diff -u --color $BASHOUT $MINIOUT
	echo
else
	printf "\n${GREEN}Test 5 passed ✅${CR}\n\n"
fi

printf "${GREEN}#--------------------------------#${CR}\n"
printf "${GREEN}|        Test 6: env             |${CR}\n"
printf "${GREEN}#--------------------------------#${CR}\n"

printf "\nTake this test with a grain of salt, there are differences,\n"
printf	"but they shouldn't be too major, confirm visually.\n"

printf "\n../minishell < minishell_test_env_input_01.sh > minishell.out\n"
printf "bash < minishell_test_env_input_01.sh > bash.out\n\n"
$MINISHELL < $TESTDIR/minishell_test_env_input_01.sh > $MINIOUT
bash < $TESTDIR/minishell_test_env_input_01.sh > $BASHOUT

printf "\nEvaluating diff -u --color bash.out minishell.out\n"
DIFF=$(diff -u --color $BASHOUT $MINIOUT)
if [ "$DIFF" ]; then
	printf "\nTest 6 diff:\n"
	diff -u --color $BASHOUT $MINIOUT
	echo
else
	printf "\n${GREEN}Test 6 passed ✅${CR}\n\n"
fi

printf "${GREEN}#--------------------------------#${CR}\n"
printf "${GREEN}|        Test 7: exit            |${CR}\n"
printf "${GREEN}#--------------------------------#${CR}\n"

MIN="-300"
MAX="300"
rm $MINIOUT $BASHOUT
SEQ=`seq $MIN $MAX`
printf "\nCalling exit <num>, where num is in range [$MIN, $MAX]\n"
echo $SEQ | tr " " "\n" > seq.temp
while read line; do
	echo "exit $line" | $MINISHELL; echo $? >> $MINIOUT
done < seq.temp 2>/dev/null
while read line; do
	echo "exit $line" | bash; echo $? >> $BASHOUT
done < seq.temp 2>/dev/null

printf "\nCalling exit with multiple arguments\n"

echo "exit one 2" | $MINISHELL 2>/dev/null
echo $? >> $MINIOUT
echo "exit 1 two" | $MINISHELL 2>/dev/null
echo $? >> $MINIOUT
echo "exit 1 2" | $MINISHELL 2>/dev/null
echo $? >> $MINIOUT
echo "exit one 2" | bash 2>/dev/null
echo $? >> $BASHOUT
echo "exit 1 two" | bash 2>/dev/null
echo $? >> $BASHOUT
echo "exit 1 2" | bash 2>/dev/null
echo $? >> $BASHOUT

printf "\nCalling exit with a single non numeric argument\n"

echo "exit a" | $MINISHELL 2>/dev/null
echo $? >> $MINIOUT
echo "exit a" | bash 2>/dev/null
echo $? >> $BASHOUT

printf "\nEvaluating diff -u --color bash.out minishell.out\n"
DIFF=$(diff -u --color $BASHOUT $MINIOUT)
if [ "$DIFF" ]; then
	printf "\n${RED}Test 7 failed ❌ ⬇️ ${CR}\n"
	diff -u --color $BASHOUT $MINIOUT
	echo
else
	printf "\n${GREEN}Test 7 passed ✅${CR}\n\n"
fi

printf "${GREEN}#--------------------------------#${CR}\n"
printf "${GREEN}|        Test 8: <               |${CR}\n"
printf "${GREEN}#--------------------------------#${CR}\n"

echo "< minishell_tester.sh cat" | $MINISHELL > $MINIOUT
echo "cat < Makefile" | $MINISHELL >> $MINIOUT
echo "cat < Makefile < not_a_file" | $MINISHELL >> $MINIOUT
echo "cat < not_a_file < Makefile" | $MINISHELL >> $MINIOUT
echo "cat < src < Makefile" | $MINISHELL >> $MINIOUT
echo "< minishell_tester.sh cat" | bash > $BASHOUT
echo "cat < Makefile" | bash >> $BASHOUT
echo "cat < Makefile < not_a_file" | bash >> $BASHOUT
echo "cat < not_a_file < Makefile" | bash >> $BASHOUT
echo "cat < src < Makefile" | bash >> $BASHOUT

printf "\nEvaluating diff -u --color bash.out minishell.out\n"
DIFF=$(diff -u --color $BASHOUT $MINIOUT)
if [ "$DIFF" ]; then
	printf "\n${RED}Test 8 failed ❌ ⬇️ ${CR}\n"
	diff -u --color $BASHOUT $MINIOUT
	echo
else
	printf "\n${GREEN}Test 8 passed ✅${CR}\n\n"
fi

rm seq.temp
