/*
 * Solution.cpp
 *
 * Author: 			Victor Reyes
 * University:  	Pontificia Universidad Catolica de Valparaiso, Valparaiso, Chile
 * Created		:	August 2th 2018
 * Last Update:   	August 2th 2018
 */


#include <Solution.h>


Solution::Solution(const SCP problem):problem(problem),fitness(0){

	for (int i ; i < problem.nb_rows ; i++)
		rowsCover.push_back(rowCovering(problem,i));
	for (int i = 0 ; i < problem.nb_columns ; i++)
		rep_solution.push_back(0);
	sorting();
}

void Solution::sorting(){
	std::sort (rowsCover.begin(), rowsCover.end(), operator());
};

void Solution::updateSolution(){
	fitness = fitness + problem.cost_vector[last_column];
	rep_solution[last_column] = 1;
	int n_rows = rowsCover.size();
	int aux = 0;
	for (int i = 0 ; i < n_rows ; i++){
		int aux2 = i - aux;
		if (problem.cover_matrix[rowsCover[aux2].row][last_column]==1)
			rowsCover.erase(rowsCover.begin()+aux2);
	}
};

