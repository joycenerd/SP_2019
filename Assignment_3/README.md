# Assignment_3 Modify Code to Double the Performance

### Explanation

First I execute the original sample code to get the time it execute. I found that the performance is pretty bad in the beginning. Now explaining how to double the performance.
1. The original program use `rand()` provide by C to generate random numbers for `table[][]`. I think this is kind of unefficient, so I wrote a random function by myself in the original file and also using it as inline function to improve the performance.
2. I think the main problem of this program is that when adding up the sum of each column the access method isn’t continuous, it jumps from one block of memory to another and all the blocks aren’t consecutive, so this will take a lot of CPU time. But I haven’t thought of a really efficient way to add up the sum of each column making the memory block of `table[][]` consecutive to access. Instead the last step I do is to simply combine rowSum and colSum. That means when calculating rowSum I calculate colSum at the same time. This can reduce one double for loop just to compute colSum itself. Although accessing `table[][]` for colSum is still jumping from memory block to block but I found that what I did makes the execute time less.

### How to use this program
1. Open terminal and change directory to this program's directory ex: 406410035_hw3
2. type `make`
3. Then the executable file `fastTable` should be in this directory
4. Then execute the program `time ./fastTable`
5. The result should be print on screen with real time, user time and system time at the end of the output.


