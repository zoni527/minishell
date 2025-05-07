export SHELL=$_
echo $SHELL
$SHELL << h
exit 100
h
echo $?
exit
