## CPU intro homework
1. (`q1.c`): Write a program that calls `fork()`. Before calling `fork()`, have the main process access a varibale and set its value to something.
2. Write a program that opens a file (with the `open()` system call) and then calls `fork()` to create a new process.

## Answers
1. What value is the variable in the child process? What happens to the variable when both the child and the parent change the value of `x_ptr`?
    - The child process first accesses `x_ptr` which is 10, it then updates it to 15.
    - The child process updates `x_ptr` to 15 while the parent process when printing out `x_ptr` prints out 10. This means the update to `x_ptr` from the child process has no effect on `x_ptr` inside of the parent process.
2. Can both the child and parent access the file descriptor returned by `open()`? What happens when they are writing to the file concurrently?
    - Both the child and the parent can access the file descriptor