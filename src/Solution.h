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
#include <SCP-utils.h>
#include <algorithm>

using namespace std;

class Solution{

	Solution(const SCP problem);

	const SCP problem;

	vector<int> rep_solution;
	vector<rowCovering> rowsCover;
	double fitness;
	int last_column;

	void sorting();
	void updateSolution();

	inline bool operator() (const rowCovering& struct1, const rowCovering& struct2)
	{
	        return (struct1.nb_covers < struct2.nb_covers);
	}
};



#endif /* SRC_SOLUTION_H_ */
