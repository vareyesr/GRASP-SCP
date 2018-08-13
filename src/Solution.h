/*
 * Solution.h
 *
 * Author: 			Victor Reyes
 * University:  	Pontificia Universidad Catolica de Valparaiso, Valparaiso, Chile
 * Created		:	August 2th 2018
 * Last Update:   	August 2th 2018
 */
#ifndef SRC_SOLUTION_H_
#define SRC_SOLUTION_H_

#include <vector>
#include <rowCovering.h>
#include <SCP.h>
#include <algorithm>
#include <set>

using namespace std;

class Solution{
public:
	Solution(const SCP problem);

	const SCP problem;
	set<int> aux_aux;
	vector<int> rep_solution;
	vector<rowCovering> rowsCover;
	double fitness;
	int last_column;

	void sorting();
	void updateSolution();
	void rowDomination();
	static bool comp(const rowCovering& lhs, const rowCovering& rhs);
};



#endif /* SRC_SOLUTION_H_ */
