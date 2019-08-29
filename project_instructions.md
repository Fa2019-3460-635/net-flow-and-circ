[copied from class website](http://www.cs.uakron.edu/~duan/class/635/projects/project1/project1.htm)

# Advanced Algorithms, Project 1 - Network Flow and Circulation with Demands Problem #

 

**Problem Description:** The objective of this project is to implement the Ford-Fulkerson network flow algorithm and then use it to solve the circulation with demands problem. Use the textbook examples and examples presented in class as test cases for your implementation to make sure that you can get the correct solutions and trace the intermediate outputs, such as, residual network, flow capacity, and augmenting flow. You should also test, analyze and measure the performance of your algorithm and implementation with many other test cases you generate on your own, e.g., extreme cases and random flow graphs. Your implementation of Ford-Fulkerson must solve the general network flow problem before you apply it to solve the circulation with demands problem.

 

You can use the formulation of the circulation with demands problem as a maximum flow problem presented at: http://www.cs.princeton.edu/~wayne/cs423/lectures/max-flow-applications (page54).
 

## Requirement: ##

- Source code 
- Group project presentation in class (20 min), Q&A (5 min)
- Individual project report (3/4 pages, no longer than 5 pages) 

**Note:**
This project is to be done in a group of two/three students. The responsibilities of the students in a group must be clearly enough delimited and stated in a statement (attached to your project) so that each of you can be graded fairly and separately.

 

## Specific requirements: ##

1. The graph must be implemented using the Adjacency List Representation, read Chapter 22 of the textbook if you need.
2. Design and implement the Breadth-First Search (BFS), read Chapter 22 of the textbook. This implementation must be a self-contained module to be applicable for any graph search problem where breadth-first search is needed.
3. Apply your BFS to find the shortest path given any graph with positive edge weights (flow capacities) and one start node and any number of goal nodes. It is critical to track the actual path here.
4. The input format for the Breadth-First Search should be an adjacency list. The output is the shortest path (in terms of # of edges). 
 -Ex. Input for the graph:

 - **TODO** graph1.png
 
 - should be:
```
1 3 2 6 3 8 //first line is reserved for node 0 which is connected to 1 with a weight 3, 2 with a weight 6,…
2 2 //second line is reserved for node 1; node 1 is connected to 2 with a weight 2
3 1 //3rd line is reserved for node 2; node 2 is connected to 3 with a weight 1
(blank line) //no outgoing edge from node 3
```
 -Output for the shortest path from 0 to 3 should be: 0, 3

5. Demonstrate that your BFS can run in time proportional to E+V (in the worst case) (you must generate large graphs to illustrate the running time of your implementation). Present your result in a table or a line graph.
6. Design your Ford-Fulkerson algorithm using the BFS. Each time you invoke the BFS module you will find a shortest path which will augment the current total flow by a positive amount. Augmenting the flow will change the capacity graph along the path just found. Use that modified capacity graph and residual flow network to find the next augmenting path.
7. The input format for the Ford-Fulkerson algorithm should be an adjacency list. The output is the value of max-flow. Your program should be able to identify which node is the source and which is the sink.
8. Design a “complete” suite of test cases that is representative for the maximum flow problem and spans a wide range of problem sizes. The test cases should include textbook examples, random test cases and some extreme cases. Discuss how and why you generated your test cases (especially the random test cases and extreme test cases) and include them in your report and submitted files.
9. Use your test cases to establish the confidence in the correctness of your program, especially, showing that the results meet your expectation. Show how well the actual performance corresponds (or even beats) the analytically predicted performance (by tables, charts and formulas). Show that your programs meet (or beat) your analysis.
10. Apply the Ford-Fulkerson algorithm to solve the circulation problem. The input of your program for the problem will an augmented Adjacency List: Ex: the input for the network:

```
-7 1 10 2 3 //1st line is reserved for node 0 which is connected to 1 with a weight 10, 2 with a weight 3; -7 is the demand
-8 2 6
10
```

Output to the problem will be either:

yes, it has a circulation. 

**- OR -** 

no, it does not have a circulation. If no, also report the reason 1) total supply!=total demand, or 2) the minimum cut. Ex: for this problem, supply>demand.

11. Design a set of test cases that include both cases and spans a wide range of problem sizes. The test cases should include small examples, random test cases and some extreme cases. Report your results on the test cases and include them in your report and submitted files.
12. Programs should be written in C++ or Java. Include a README file to give the reader a high-level explanation of your implementation and anything we need to know to run your program.
13. We’ll test your program using the commands such as the following (make sure you can run your program the same way!):
```bash
yourProgram.exe –b graph.txt 0 3 # testing your Breadth-First Search implementation; 0=source, 3=target.

yourProgram.exe –f graph.txt # testing your Ford-Fulkerson implementation

yourProgram.exe –c circulation.txt #testing your application to the circulation problem
```

14. Your report should include the following sections:
  * Describe your algorithm clearly in modules.
  * Describe the data structure you use for each module, with justification for your choices including why/why not adjacency list is a good choice for your application.
  * Discuss any implementation difficulties you encountered, and how you overcame them.
  * Theoretical analyses and experimental run results (with timing). Attach your own test cases for each module.
  * Discuss any insights on the problem and algorithm (efficiency, modularity, generalizability, etc.).
  * Describe your test cases and test-case results.
15. Your presentation should be prepared using Microsoft PowerPoint. You need to perform a live demo with provided test cases.

 

## Submission instructions: ##
When you are ready to submit, obtain a printed copy of your program. Remember to sign and attach the required Academic Integrity Pledge cover sheet. The printed program and cover sheet must be turned in to your instructor by the start of class on the date the program is due. You must submit an electronic copy of the program using our drop box at Brightplace. You are required to zip your submission inside an archive. Follow these steps:

Create a folder named zippy_1 (but use your group's name). 
Place just the source files inside the folder.
Right-click on the folder and choose Send To... Compressed Folder (or use some other Zip utility to archive the entire folder). The goal is to create a zip archive named zippy_1.zip (your group name) that contains the folder which contains the source files for your project. 
Drop this single zipped file in your dropbox at Brightplace. Each group needs to submit only one copy. 
Please pay attention to the naming conventions for the submission files. These must be followed exactly in order to receive credit. Invalid submissions will need to be resubmitted with a penalty assessed.

Be sure to electronically submit your working solution before the due date! Do not submit non-working programs. The electronic submission time will be used to assess late penalties.

Presentation schedule:
