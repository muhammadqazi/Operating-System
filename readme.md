# Operating-System

# Project Outline : 

Program that simulates the service of jobs (process) by the CPU of a multi-user computer. Inputs should be taken from text file with command arguments. And results also should be written to output file and screen.


## Setup

For some machines it needs sudo permission
```
g++ main.cpp -o main
```

```
./main -f input.txt -o output.txt   
```

To run the program two flags are required from the user ```-f``` which is for getting input for progran and ```-o``` to store the output result from the program.


**Input.txt

Input file data should be in the following format :

```bursty_time : arrival_time : priority ```
