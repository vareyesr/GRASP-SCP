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

	for (int i=0 ; i < problem.nb_rows ; i++)
		rowsCover.push_back(rowCovering(problem,i));
	for (int i = 0 ; i < problem.nb_columns ; i++)
		rep_solution.push_back(0);
	sorting();
}



bool Solution::comp(const rowCovering& lhs, const rowCovering& rhs)
{
  return lhs.nb_covers < rhs.nb_covers;
}
void Solution::sorting(){
	std::sort (rowsCover.begin(), rowsCover.end(), comp);
};



void Solution::updateSolution(){

	fitness = fitness + problem.cost_vector[last_column];
	rep_solution[last_column] = 1;
	int n_rows = rowsCover.size();
	int aux = 0;
	for (int i = 0 ; i < n_rows ; i++){
		int aux2 = i - aux;
		if (problem.cover_matrix[rowsCover[aux2].row][last_column]==1){
			rowsCover.erase(rowsCover.begin()+aux2);
			aux++;
		}
	}
};

void Solution::rowDomination(){

	int nb_dominated = 0;
	for (int i = 0 ; i < rowsCover.size(); i++){
		if (rowsCover[i].nb_covers > 1)
			break;
		else
			nb_dominated++;
	}

	for (int i = 0 ; i < nb_dominated ; i++){
		last_column = rowsCover[0].col_covering[0];
		updateSolution();
	}

};

