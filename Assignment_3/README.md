# Assignment_3 Modify Code to Double the Performance

### Explanation

First I execute the original sample code to get the time it execute. I found that the performance is pretty bad in the beginning. Now explaining how to double the performance.
1. Before revising any code inside the `table.c` file, the first thing I do is create a makefile. I specify to compile the code with `-O3`. This greatly improve the performance.
2. The original program use `rand()` provide by C to generate random numbers for `table[][]`. I think this is kind of unefficient, so I wrote a random function by myself in the original file and also using it as inline function to improve the performance.
3. There are many double loops inside the program, but I found most of the second for loops are useless, since they only left the last element at the end. So I delete most of the second for loop and only assign the last element as the index. This definitely improve the performance since the time complexity in some function reduce from `O(N^2)` to `O(n)`.

### How to use this program
1. Open terminal and change directory to this program's directory ex: 406410035_hw3
2. type `make`
3. Then the executable file `fastTable` should be in this directory
4. Then execute the program `time ./fastTable`
5. The result should be print on screen with real time, user time and system time at the end of the output.


