# Assignment_4 Recursively List Files and Directory and Intercept all the Events Related to It

### Explanation

1. hw4_dir: In this program I modify the original code lisDirRec.c. The only thing I do is to change the output order. The order will be sorted beforehand by filename's alphabetical order. How I do is to split file and directory into two piles. First sort the files by alphabetical order using `qsort` and output. I sort the directory too! While ouput the directory I go into the directory to list the files and directory in the same manner(sorted) in this directory. This is by calling `listDir` whenever encountering a directory.
2. hw4_inotify: The user can give the directory or file they want to intercept to this program. The program will intercept all the events that happens to the directory/file and also all the subdirectory too! This is by copying the listDir from `hw4_dir.c` to `inotify.c` and save that to inotify list. So the program will get the path of all the files and directory to do inotify.

### How to use this program
1. Open terminal and change directory to this program's directory ex: 406410035_hw4
2. type `make`
3. Then the executable file `hw4_dir` and `hw4_inotify` should be in this directory
4. Then execute the program `./hw4_dir [dirname]` -> This is like `ls` but it will list all the files and directories, subdirectories related to [dirname] in alphabetical order
5. Execute the program `./hw4_inotify [dirname]` -> This will intercept all the events related inside the [dirname] (files,subdirectories)
6. All the result will be output on the screen
