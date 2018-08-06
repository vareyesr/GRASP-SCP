/*
 * GRASP.h
 *
 * Author: 			Victor Reyes
 * University:  	Pontificia Universidad Catolica de Valparaiso, Valparaiso, Chile
 * Created		:	August 1th 2018
 * Last Update:   	August 6th 2018
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
	bool repairing(Solution& solution,vector <int> rep_columns);
	void construction(bool repairing,Solution &solution);
	void penalty(Solution& solution);
	void report();
	void update_best_sol(Solution solution);
	pair<vector<int>,vector<int>> divide_list(vector<int> input_list);
	void init_lists(vector <vector <int> > & rep_lists, int nb_lists);
};


#endif /* SRC_GRASP_H_ */
