# A GRASP strategy for the set covering problem.

This version is being developed in c++11. 
Last update was on August 2018

**Description**
The algorithm works in two phases. The first phase consists in constructing iterative a solution using a set of simple rules for evaluating and instantiating the columns of the input matrix A. After the solution is constructed we proceed to repair it. In this phase we use a *Divide and Conquer* scheme for dividing the solution, resetting a part of it and starting the search again from this point. The whole procedure is repeated until reaching a time limit.

Additionally, we use a reward/penalty mechanism for weighting the columns of the matrix in order to accelerate the convergence of the whole strategy.

**To compile**
```
g++ -I src/ -std=c++11 main.cpp src/SCP.cpp src/GRASP.cpp src/Solution.cpp src/rowCovering.cpp src/SCP-utils.cpp -o GRASP-SCP
```

**Execution example**

```
./GRASP-SCP ./benchs/scp41.txt 100 1
```
 
# Authors

* **Victor Reyes** - PUCV - [webpage](https://sites.google.com/view/csvictor-reyes)
 
