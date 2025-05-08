```
main
i = 0
    new pipe -> [3]pipe[4]
    child[READ]     = [-1]
    child[WRITE]    = [3]
    fork
        child 0:
            child[READ]     = [-1]
            child[WRITE]    = [3]
            extra open fd:  = [4]
                -> close[4]
    prev_pipe_read_fd = [4]
    close[3]
i = 1
    new pipe -> [5]pipe[6]
    child[READ] = prev_pipe_read_fd = [4]
    child[WRITE] = [5]
    fork
        child 1:
            child[READ]     = [4]
            child[WRITE]    = [5]
            extra open fd:  = [6]
                -> close[6]
    prev_pipe_read_fd = [6]
    close[5]
i = 2
    no new pipe
    child[READ] = prev_pipe_read_fd = [6]
    child[WRITE] = [-1]
    fork
        child 2:
            child[READ]     = [6]
            child[WRITE]    = [-1]
            extra open fd:  = [-1]
    close[6]
```
