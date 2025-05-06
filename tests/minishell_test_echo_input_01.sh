echo
echo "Command: echo Hello"
echo Hello
printf "%s\n\n" "exit value: $?"

echo 'Command: echo "Hello"'
echo "Hello"
printf "%s\n\n" "exit value: $?"

echo "Command: echo 'Hello'"
echo 'Hello'
printf "%s\n\n" "exit value: $?"

echo "Command: Hello world"
echo Hello world
printf "%s\n\n" "exit value: $?"

echo 'Command: echo "Hello world"'
echo "Hello world"
printf "%s\n\n" "exit value: $?"

echo "Command: echo 'Hello world'"
echo 'Hello world'
printf "%s\n\n" "exit value: $?"

echo "Command: echo -n No newline"
echo -n No newline
printf "%s\n\n" "exit value: $?"

echo "Command: echo -n"
echo -n
printf "%s\n\n" "exit value: $?"

echo "Command: echo test -n"
echo test -n
printf "%s\n\n" "exit value: $?"

echo "Command: echo 1"
echo 1
printf "%s\n\n" "exit value: $?"

echo "Command: echo -nnnnnnn No newline again"
echo -nnnnnnn No newline again
printf "%s\n\n" "exit value: $?"

echo "Command: echo -nnnnnnz No newline again"
echo -nnnnnnz No newline again
printf "%s\n\n" "exit value: $?"

echo 'Command: echo $USER'
echo echo $USER
printf "%s\n\n" "exit value: $?"

echo 'Command: echo $abc'
echo echo $abc
printf "%s\n\n" "exit value: $?"

echo 'Command: echo onte $two three'
echo echo one $two three
printf "%s\n\n" "exit value: $?"
