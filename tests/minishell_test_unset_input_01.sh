export one two three
export
unset one two three
echo $?
export
export three=3 four=4 five=5
export
unset three four five
echo $?
export
unset not in the env
echo $?
export
