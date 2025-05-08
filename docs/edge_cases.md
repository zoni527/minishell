```
'"'"                                        ->  counting quotes not enough
multiple heredocs                           ->  required?
cat file.txt | cat < another_file.txt | cat ->  what is happening vs what should happen
>|                                          ->  multiple operators syntax error
awk                                         ->  handle white space within quotes
cd ""                                       ->  goes nowhere
cd $asdlfsdf                                ->  invalid variable expansion goes to home
cd < .gitignore ""                          ->  returns nothing / goes nowhere
cd ""test
cd "" test
$abc echo hello
export abc=test
export abc
export test+=test
export test+=test2
export 1test
export -test
export te+st
export tes-t
export test+
export t1est
export _test
export t_est
```
