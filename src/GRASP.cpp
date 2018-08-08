/*
 * GRASP.cpp
 *
 * Author: 			Victor Reyes
 * University:  	Pontificia Universidad Catolica de Valparaiso, Valparaiso, Chile
 * Created		:	August 1th 2018
 * Last Update:   	August 6th 2018
 */

#include <GRASP.h>


GRASP::GRASP(const SCP problem, Solution solution,double MAX_TIME, double start_time): problem(problem), MAX_TIME(MAX_TIME), start_time(start_time),
																	best_solution(999999), best_time(-1), solution(solution){

}


void GRASP::search(){

	while(double(clock()-start_time) / CLOCKS_PER_SEC < MAX_TIME){
		Solution solution_aux = solution;
		while(!solution_aux.rowsCover.empty())
			construction(false,solution_aux);
		update_best_sol(solution_aux);
		bool repairing_successful = true;
		vector <vector <int> > rep_lists;
		while (repairing_successful){
			repairing_successful = false;
			init_lists(rep_lists,2);
			while(rep_lists.size() > 0){
				Solution solution_empty = solution;
				if (repairing(solution_empty,solution_aux,rep_lists[rep_lists.size()-1])){
					pair<vector<int>,vector<int>> new_lists = divide_list(rep_lists[rep_lists.size()-1]);
					repairing_successful = true;
					rep_lists.pop_back();
					rep_lists.push_back(new_lists.first);
					rep_lists.push_back(new_lists.second);
				}
				else
					rep_lists.pop_back();
			}
		}
		penalty(solution_aux);
	}
}

void GRASP::construction(bool repairing, Solution& solution){
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
		if (value < h_value){
			h_value = value;
			solution.last_column = c_column;
		}

		if (!repairing){
			total_sum = total_sum + value;
			heuristic_values.push_back(make_pair(c_column,value));
		}
	}
	/*roulette selection*/
	if ((!repairing) && (rand()%10==0)){
		double rand_number = ((double) rand() / RAND_MAX);
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
	solution.updateSolution();
}

bool GRASP::repairing(Solution empty_solution, Solution& solution,vector <int> rep_columns){


	for (int i = 0 ; i < rep_columns.size() ; i++){
		if (solution.rep_solution[rep_columns[i]] == 1){
			if (empty_solution.rep_solution[rep_columns[i]] != 1){
				empty_solution.last_column = rep_columns[i];
				empty_solution.updateSolution();
			}
		}
	}

	while(!empty_solution.rowsCover.empty())
		construction(true,empty_solution);


	if (empty_solution.fitness < solution.fitness){
		copy_solution(empty_solution,solution);
		update_best_sol(solution);
		return true;
	}
	else
		return false;
}

void GRASP::penalty(Solution& solution){


}

void GRASP::report(){
	cout << problem._input << " " << best_solution << " " << best_time << endl;
}

void GRASP::update_best_sol(Solution solution){
	if (solution.fitness < best_solution){
		best_solution = solution.fitness;
		best_time = double(clock()-start_time) / CLOCKS_PER_SEC;
	}
}

pair<vector<int>,vector<int>> GRASP::divide_list(vector<int> input_list){
	pair<vector<int> , vector<int> > _new_lists;
	for (int i = 0 ; i <input_list.size() ; i++){
		if (rand()%2 != 0) _new_lists.first.push_back(i);
		else _new_lists.second.push_back(i);
	}
	return _new_lists;
}

void GRASP::init_lists(vector <vector <int> > & rep_lists, int nb_lists){
	vector<int> _aux;
	for (int i = 0 ; i < nb_lists ;i++)
		rep_lists.push_back(_aux);
	for (int i = 0 ; i < problem.nb_columns ; i++){
		if (solution.rep_solution[i] == 0){
			rep_lists[rand()%nb_lists].push_back(i);
		}
	}
}

void GRASP::copy_solution(Solution old_sol,Solution& new_sol){
	new_sol.fitness = old_sol.fitness;
	new_sol.last_column = old_sol.last_column;
	for (int i = 1 ;  i < new_sol.rep_solution.size() ; i++)
		new_sol.rep_solution[i] = old_sol.rep_solution[i];
}
