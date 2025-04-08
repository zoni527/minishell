# minishell input tests

## Base cases

### Builtins

#### echo

```bash
echo
echo Hello
echo Hello World!
echo "Hello World!"
echo 'Hello World!'
echo "Hello $USER!"
echo 'Hello $USER!'
echo $non_existing
echo "$non_existing"
```

#### cd

### Pipes

```bash
echo hello | cat
echo hello | cat | wc
cat Makefile | grep "NAME"
cat Makefile | grep "$" | wc -l
sleep 1 | sleep 2 | sleep 3 | sleep 4 | sleep 5 | sleep 6
```

### Redirection: input

```bash
cat < infile.txt
< infile.txt cat
cat < infile1.txt < infile2.txt
< infile1.txt < infile2.txt cat
```

### Redirection: output

```bash
ls > out.txt
> out.txt ls
ls > out1.txt > out2.txt
> out1.txt > out2.txt ls
```

### Redirection: append

```bash
ls >> out.txt
>> out.txt ls
ls >> out1.txt >> out2.txt
>> out1.txt >> out2.txt ls
```

### Heredoc

```bash
<< STOP
```

## More advanced cases

```bash
echo echo
ls | cat > cat_ls.txt | grep "cat_ls.txt"
ls | cat > cat_ls.txt | cat | echo Hello
```
