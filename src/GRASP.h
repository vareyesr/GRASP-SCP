/*
 * GRASP.cpp
 *
 * Author: 			Victor Reyes
 * University:  	Pontificia Universidad Catolica de Valparaiso, Valparaiso, Chile
 * Created		:	August 1th 2018
 * Last Update:   	August 2th 2018
 */

#ifndef SRC_GRASP_H_
#define SRC_GRASP_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <SCP.h>
#include <SCP-utils.h>
#include <rowCovering.h>
#include <Solution.h>

using namespace std;

class GRASP{

	GRASP(const SCP problem, Solution solution, double MAX_TIME, double start_time);


	const SCP problem;
	double MAX_TIME;
	double start_time;
	Solution solution;

	double best_solution;
	double best_time;

	void search();
	void repairing();
	void construction(bool repairing);
	void penalty();
};


#endif /* SRC_GRASP_H_ */
