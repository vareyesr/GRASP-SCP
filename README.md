# A GRASP strategy for the set covering problem.

This version is being developed in c++11. 
Last update was on August 2018

**To compile**
```
g++ -I src/ -std=c++11 main.cpp src/SCP.cpp src/GRASP.cpp src/Solution.cpp src/rowCovering.cpp src/SCP-utils.cpp -o GRASP-SCP
```

**Execution example**

```
./GRASP-SCP ./benchmarks/scp49.cpp 100 1
```
 
# Authors

* **Victor Reyes** - PUCV - [webpage](https://sites.google.com/view/csvictor-reyes)
 