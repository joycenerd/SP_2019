# Assignment_5 Fork and Simple Shell

### Explanation

1. hw5-1: This program is to count the total process are there after `fork()` four times. I change a bit of sample code fork.c and wait.c. I define parent pid, child pid and the counter to count the process in the program. When child is executing that means the program is on the fork branch. I will use `WEXITSTATUS` to get the last status -> counter at that time, so my counter won't be lost while forking out. I use `waitpid` to wait for child to execute finish so there will be no zombie process generate. The counter initialize to 1 because original parent process is a process too. At last I print out all the pis and the counter in accordance to it. When the program ended I get total of **16** process.

### How to use this program
1. Open terminal and change directory to this program's directory ex: 406410035_hw4
2. type `make`
3. Then the executable file `hw4_dir` and `hw4_inotify` should be in this directory
4. Then execute the program `./hw4_dir [dirname]` -> This is like `ls` but it will list all the files and directories, subdirectories related to [dirname] in alphabetical order
5. Execute the program `./hw4_inotify [dirname]` -> This will intercept all the events related inside the [dirname] (files,subdirectories)
6. All the result will be output on the screen