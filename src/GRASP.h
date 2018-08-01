/*
 * GRASP.cpp
 *
 * Author: 			Victor Reyes
 * University:  	Pontificia Universidad Catolica de Valparaiso, Valparaiso, Chile
 * Created		:	August 1th 2018
 * Last Update:   	August 1th 2018
 */

#ifndef SRC_GRASP_H_
#define SRC_GRASP_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <SCP.h>

using namespace std;

class GRASP{

	GRASP(const SCP problem, double MAX_TIME, double start_time);


	const SCP problem;
	double MAX_TIME;
	double start_time;

	double best_solution;
	double best_time;


	void search();
	void repairing();
	void rowDomination();
	void construction();

};


#endif /* SRC_GRASP_H_ */
