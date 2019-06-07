# Assignment_5 Fork and Simple Shell

### Explanation

1. hw5-1: The purpose of this program is to count the total processes are there after `fork()` four times. I change a bit of sample code fork.c and wait.c. I define parent pid, child pid and the counter to count the process in the program. When child is executing that means the program is on the fork branch. I will use `WEXITSTATUS` to get the last status -> counter at that time, so my counter won't be lost while forking out. I use `waitpid` to wait for child to execute finish so there will be no zombie process generate. The counter initialize to 1 because original parent process is a process too. At last I print out all the pid and the counter in accordance to it. When the program ended I get total of **16** processes.
2. HW5-2: The purpose of this program is to modified the previous myShell.c code. Change the function `execvp()` to `execle()`. The two functions usage is a bit different, especially the parameter that passed into the function is really different. Different system call need a different path. What I do is to specify all the possibility by myself. First specify my environment argument `char *env[] = {getenv("HOME"), "LOGNAME=home", (char *)0};`
    * `cd`: change directory immediately, no need to go into `execle()`
    * other system calls: before writing this program I use `echo $PATH` to see all the path. What I do is to copy all the possible path to my program. So when using the system call in my shell, I try all the paths. If none of them match (all return -1) than there will be two possibilities. One, this is an invalid command. Second, this is an executable file. Which will be explain in the next point.
    * other executable file like ./hw5-1: `execle(argVect[0], argVect[0], (char *)0, env)`

    The downside of the program is although I did find the right path to process the command, but this is still a simple shell that I make. It has some drawbacks. ex:
        * when using `echo $PATH`: instead of outputting the whole path arguments, it only output $PATH
        * `vim file.c`: if do any changes in vim, it can't save the changes
        * `./hw5-1 > test.txt`: it should output the result to the file test.txt, but instead it only output on screen
        * `time ./hw5-1`: the time it measure will always output 0.00
    These are just some of the drawback I encountered, in reality it may have more

### How to use this program
1. Open terminal and change directory to this program's directory ex: 406410035_hw5
2. type `make`
3. Then the executable file `hw5-1` and `hw5-2` should be in this directory
4. Then execute the program `./hw5-1` -> All the process pid and counter will be print on the screen
5. Execute the program `./hw5-2` -> This is a simple shell. All the system calls it can accept written above the explanation
