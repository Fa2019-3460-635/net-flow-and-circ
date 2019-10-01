# Advanced Algorithms, Project 1 - Network Flow and Circulation with Demands Problem #

An implemenation of the Edmonds-Karp algorithm, a dirivative of the Ford-Fulkerson algorithm that makes use of a path-finding algorithm to determine the next augmenting path. 

Graphs are read in from a text file into an adjacency list data structure to be processed by one of three methods:
- Breadth-first search (BFS)
- Ford-Fulkerson (implemented using BFS)
- Circulation Identification

## Authors: ## 
- Sean Collins 
- Andrew Robinson 
- Edwin Sarver

**NOTE:** All instructions assume this project is being used on a Linux-based system.

---

## Building ##
**NOTE**: The google test library is pulled down during the first build 
automatically. Be sure you are connected to the internet before your first build.

In a terminal within the project directory:

```bash
mkdir build # create a build folder in the project directory
cd build # navigate into that build folder
cmake .. # run cmake to generate makefiles
make -j4 # build using 4 concurrent threads (increase the number if desired) 
```

---

## Running the Application ##

In a terminal within the project `build` directory after a build has been completed:

```bash
cd bin
# find the shortest path between nodes 0 and 16 from a graph given in graph.txt
# by using the breadth-first search (BFS) algorithm. 
./project_one -b graph.txt 0 16

# find the maximum flow of the graph given in graph.txt by
# using the Ford-Fulkerson method
./project_one -f graph.txt

# Determine wether the graph given in graph.txt has circulation
./project_one -c graph.txt

# Get usage information
./project_one -h
```

---

## Running Unit Tests ##
The tests for this project are written using the google test framework.
There are a couple ways the run the unit tests for this project.

In a terminal within the `build` folder in the project directory after a build has been completed:

#### Option 1: `make test` ####
```bash
make test
```

#### Option 2: `ctest` ####
```bash
ctest # use '-V' option for more information.
```

#### Option 3: Run Test Binaries Individually ####
```bash
cd bin
./*-tests
```

---

## Running Benchmarks and Generating Plots

**NOTE**: Python and "pipenv" must be installed in order to successfully carry
          out the following instructions.

In a terminal within the project `build` directory, run:

```bash
make plots
```
