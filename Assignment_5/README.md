# Assignment_5 Fork and Simple Shell

### Explanation

1. hw5-1: The purpose of this program is to count the total processes are there after `fork()` four times. I change a bit of sample code fork.c and wait.c. I define parent pid, child pid and the counter to count the process in the program. When child is executing that means the program is on the fork branch. I will use `WEXITSTATUS` to get the last status -> counter at that time, so my counter won't be lost while forking out. I use `waitpid` to wait for child to execute finish so there will be no zombie process generate. The counter initialize to 1 because original parent process is a process too. At last I print out all the pid and the counter in accordance to it. When the program ended I get total of **16** processes.
2. HW5-2: The purpose of this program is to modified the previous myShell.c code. Change the function `execvp()` to `execle()`. The two functions usage is a bit different, especially the parameter that passed into the function is really different. Different system call need a different path. What I do is to specify all the possibility by myself. First specify my environment argument `char *env[] = {getenv("HOME"), "LOGNAME=home", (char *)0};`
    * `cd`: change directory immediately, no need to go into `execle()`
    * `ls`: `execle("/bin/ls", argVect[0],argVect[1]..., (char *)0, env)`
    * `vim`: `execle("/usr/bin/vim", argVect[0], argVect[1], (char *)0, env)`
    * `more`: `execle("/bin/more", argVect[0], argVect[1], (char *)0, env)`
    * `less` and `time`: although I can find the correct path but it didn't function properly so I think this is only half working
    * other executable file like ./hw5-1: `execle(argVect[0], argVect[0], (char *)0, env)`
Since there are too many system call to think of and each call has there own path to call, above are all the functions I do.


### How to use this program
1. Open terminal and change directory to this program's directory ex: 406410035_hw5
2. type `make`
3. Then the executable file `hw5-1` and `hw5-2` should be in this directory
4. Then execute the program `./hw5-1` -> All the process pid and counter will be print on the screen
5. Execute the program `./hw5-2` -> This is a simple shell. All the system calls it can accept written above the explanation
