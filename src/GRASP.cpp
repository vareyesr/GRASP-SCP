/*
 * GRASP.cpp
 *
 * Author: 			Victor Reyes
 * University:  	Pontificia Universidad Catolica de Valparaiso, Valparaiso, Chile
 * Created		:	August 1th 2018
 * Last Update:   	August 2th 2018
 */

#include <GRASP.h>


GRASP::GRASP(const SCP problem, Solution solution,double MAX_TIME, double start_time): problem(problem), MAX_TIME(MAX_TIME), start_time(start_time),
																	best_solution(-1), best_time(-1), solution(solution){

}


void GRASP::search(){


}

void GRASP::construction(bool repairing){
	int function;
	if (repairing) function = 0;
	else function = rand()%5;
	double h_value = 99999999;
	double total_sum = 0;

	vector < pair < int, double> > heuristic_values;
	for (int j = 0 ; j < solution.rowsCover[0].nb_covers ; j++){
		int c_column = solution.rowsCover[0].col_covering[j];
		int rows_to_be_covered = 0;
		for (int i = 0 ; i < solution.rowsCover.size(); i++){
			int c_row = solution.rowsCover[i].row;
			if (problem.cover_matrix[c_row][c_column] == 1)
				rows_to_be_covered++;
		}
		double value;
		switch(function){
		case 0 :	value = (double)(problem.cost_vector[c_column]/rows_to_be_covered);
					break;
		case 1 : 	value = (double)(problem.cost_vector[c_column]/log(1+rows_to_be_covered));
					break;
		case 2 : 	value = (double)(problem.cost_vector[c_column]/sqrt(rows_to_be_covered));
					break;
		case 3 : 	value = (double)(problem.cost_vector[c_column]/(rows_to_be_covered*rows_to_be_covered));
					break;
		case 4 : 	value = (double)(sqrt(problem.cost_vector[c_column])/rows_to_be_covered);
					break;
		case 5 : 	value = (double)(problem.cost_vector[c_column]/(rows_to_be_covered*log(1+rows_to_be_covered)));
					break;
		}
		if (repairing){
			if (value < h_value){
				h_value = value;
				solution.last_column = c_column;
			}
		}
		else{
			total_sum = total_sum + value;
			heuristic_values.push_back(make_pair(c_column,value));
		}
	}
	/*roulette selection*/
	if (!repairing){
		double rand_number = ((double) rand / RAND_MAX);
		for (int i = 0 ; i < heuristic_values.size() ; i++)
			heuristic_values[i].second = (1-(heuristic_values[i].second/(total_sum)))/(heuristic_values.size()-1);

		total_sum = 0;
		for (int i = 0 ; i < heuristic_values.size() ; i++){
			total_sum = total_sum+heuristic_values[i].second;
			heuristic_values[i].second = total_sum;
		}

		for (int i =  0; i < heuristic_values.size() ; i++)
			if (rand_number <= heuristic_values[i].second){
				solution.last_column = heuristic_values[i].first;
				break;
			}
	}
}

void GRASP::repairing(){


}

void GRASP::penalty(){


}
