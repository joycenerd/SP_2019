# Assignment_2 Calculate Fibonacci Number to 1000 and Analyze Program


### How this Program Works

Everyone know fib[i]=fib[i-1]+fib[i-2], so Fibonacci number grows really fast and just a few steps it will be out of integer size. Since this Assignment needs to calculate to fib[1000], I decided to use string to do the arithmetic. The main function is only for copy fib[i-1] into fib2, fib[i-2] into fib1, and output each fib[i] after every computation. Most of the work is in computeFib function. In this function, first I reverse the two string fib1 and fib2, so that the smallest digit aligned. Then I add the number digit by digit, if it's larger than ten, I carry to the next digit. After the computation I reverse my result again so I get the right answer and pass it back to my main function for output. The result will be output to a file `fib.txt`. This result than become fib[i-1] and the original fib1 will be fib[i-2]. Repeat the process until fib[1000].

# How to use this Program

1. Open terminal change directory to this program's directory ex: 406410035_hw2
2. type `make`
3. Then the executable file `fib` should be in this directory
4. Then execute the program `./fib`
5. The result will be in the `fib.txt` in this directory
