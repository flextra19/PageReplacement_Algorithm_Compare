# PageReplacementAlgorithm_C-
use Matlab to plot each algorithm performance




 Overview
In this project, we are going to write a program that implements several virtual-memory page replacement algorithms. The goal of this project is to compare and assess the impact of these algorithms on the number of page faults incurred across a varying number of physical-memory page frames available.
1.1 Page replacement Algorithms
We are going to implement the following page replacement algorithms that we discussed in class:
1. First-In, First-Out (FIFO)
2. Least Recently Used (LRU)
3. Optimal (OPT)
Implement the algorithms so that the number of page frames available can be passed in as an argument.
1.2 Performance Metric
We are interested in computing the following metric: • The number of page faults incurred
2 The Process
First, generate a random page-reference string, of size 100, where virtual page numbers range from 0 to 49. Apply the random page-reference string to each algorithm, and record the number of page faults incurred by each algorithm. Assume that demand paging is used. Structure the program to run so that you vary the number of physical-memory page frames available from 1 to 30.
3 Submission details
Submission will be done via email to jmp329@txstate.edu. The subject of the email should be “CS4328: Program 2”.
Submissions will include the source code and instructions for how to compile and run the program on one of the CS Linux servers, along with a report containing the results of the runs and their interpretation.
The report should include a single plot for the above metric. The plot on the x-axis will vary the number of page frames available, and represent the number of page faults on the y-axis, with a different-color line for each of the three algorithms.
Page 1 of 2
See example plot on page 415 (Fig. 9.13).
You can write your program in any of these languages (C, C++, Python or Java), however, it is your responsibility to ensure it runs under the CS Linux servers with a command line – nothing graphical (GUI-based). Please indicate clearly how to compile and run your program.


• Instruction of how to run:
1. Move two files in source folder ( main.cpp and testBash.command) in the current
user directory.
2. Create a simdata.txt and data folder in the location
3. In the terminal, type: ./testBash.command
4. The output 30 files will store in the data folder

• My steps of doing this project.
step1: write C++ code with three algorithms.
step2: run the testBash in terminal, then generate 30 files with three results(FIFO, OPT, LRU) in each file.
step3: wite c++ code( to organize 30 files. Put FIFO datas into outputFIFO.txt, OPT datas into outputOPT.txt and LRU datas into outputLRU.txt. Show as below.
step4: use MATLAB to plot these 3 output datas.
    

My conclusion: I was thinking about FIFO will generate the biggest page faults number always. However, from the picture, the result is vary from algorithm to algorithm.
1. When page number (red line) range (0~4),(16~18),(26~27), FIFO generate more page faults than others.
2. When page number (blue line) range (7~10),(13~18),(23~25),(28~30),OPT generate more page faults than others.
3. When page number (purple line) range (5~6), (11~12),(19~22),LRU generates more page faults than others.
