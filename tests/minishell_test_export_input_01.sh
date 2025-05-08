unset _
export
echo $?
export var1
echo $?
export | grep var1
echo $?
export $USER=
echo $?
export | grep $USER
echo $?
export $INVALID
echo $?
export
echo $?
export one two= three=three wr+ong four="one two three four"
echo $?
export
echo $?
export five+=
echo $?
export | grep five
echo $?
export six+=six
echo $?
export | grep six
echo $?
export six
echo $?
export | grep six
echo $?
export seven=seven
echo $?
export | grep seven
echo $?
export seven+=seven
echo $?
export | grep seven
echo $?
export seven+=
echo $?
export | grep seven
echo $?
export 1test
echo $?
export -test
export +test
echo $?
export te+st
echo $?
export te-st
echo $?
export test+
echo $?
export test-
echo $?
export t1est
echo $?
export test1
echo $?
export _test
echo $?
export t_est
echo $?
export test_
echo $?
export
echo $?
