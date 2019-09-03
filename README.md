# Advanced Algorithms, Project 1 - Network Flow and Circulation with Demands Problem #

**TODO** Write beautiful, concise description of our project.

---

## Building ##
**NOTE**: The google test library is pulled down during the first build automatically. Be sure you are connected to the internet before your first build.

### On Linux ###
In a terminal within the project directory:

```bash
mkdir build
cd build
cmake ..
make -j4 #use number of desired concurrent-build threads
```

### On Windows ###
**TODO**

---

## Running Unit Tests ##
The tests for this project are written using the google test framework.
There are a couple ways the run the unit tests for this project.

### On Linux ###
In a terminal within the `build` folder in the project directory after a build has been completed:

#### Option 1: ####
```bash
make test
```

#### Option 2: ####
```bash
ctest # use '-V' option for more information.
```

#### Option 3: ####
**NOT YET IMPLEMENTED**
```bash
cd bin/test
./*
```


### On Windows ###
**TODO**

---

## Running the Application ##

## On Linux ##
In a terminal within the project `build` directory after a build has been completed:

```bash
cd bin
./<PROGRAM_NAME>
```
**TODO** Move output executables the build/bin/ folder in CMake. 
