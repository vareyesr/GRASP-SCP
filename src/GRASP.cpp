/*
 * GRASP.cpp
 *
 * Author: 			Victor Reyes
 * University:  	Pontificia Universidad Catolica de Valparaiso, Valparaiso, Chile
 * Created		:	August 1th 2018
 * Last Update:   	August 6th 2018
 */

#include <GRASP.h>


GRASP::GRASP(const SCP problem, Solution solution,double MAX_TIME): problem(problem), MAX_TIME(MAX_TIME), start_time(clock()),
																	best_solution(999999), best_time(-1), solution(solution),t_lastsol(clock()){

	init_weights();

}


void GRASP::search(){
	Solution solution_empty = solution;
	while((double(clock()-start_time) / CLOCKS_PER_SEC < MAX_TIME)){
		Solution solution_aux = solution;
		while(!solution_aux.rowsCover.empty()){
			construction(true,solution_aux);
		}
		update_best_sol(solution_aux);
		bool repairing_successful = true;
		vector <vector <int> > rep_lists;
		Solution before_repairing = solution_aux;

		while ((repairing_successful) || (rand()%75!=0)) {
			repairing_successful = false;
			init_lists(rep_lists,2,solution);

			while(rep_lists.size() > 0){
				if (repairing(solution_empty,solution_aux,rep_lists[rep_lists.size()-1])){
					repairing_successful = true;

					if (rep_lists[rep_lists.size()-1].size() > 4){
						pair<vector<int>,vector<int>> new_lists = divide_list(rep_lists[rep_lists.size()-1]);
						rep_lists.pop_back();
						rep_lists.push_back(new_lists.first);
						rep_lists.push_back(new_lists.second);
					}
					else rep_lists.pop_back();
				}
				else
					rep_lists.pop_back();
			}

		}

		penalty(before_repairing,solution_aux);


	}
}

void GRASP::construction(bool repairing, Solution& solution){
	int function;
	if (repairing) function = 0;
	else function = rand()%2;
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
		case 0 :	value = (double)((problem.cost_vector[c_column]/rows_to_be_covered)*weights[c_column]);
					break;
		case 1 : 	value = (double)((problem.cost_vector[c_column]/log(1+rows_to_be_covered))*weights[c_column]);
					break;
		case 2 : 	value = (double)((problem.cost_vector[c_column]/sqrt(rows_to_be_covered))*weights[c_column]);
					break;
//		case 3 : 	value = (double)((problem.cost_vector[c_column]/(rows_to_be_covered*rows_to_be_covered))*weights[c_column]);
//					break;
//		case 4 : 	value = (double)((sqrt(problem.cost_vector[c_column])/rows_to_be_covered)*weights[c_column]);
//					break;
//		case 5 : 	value = (double)((problem.cost_vector[c_column]/(rows_to_be_covered*log(1+rows_to_be_covered)))*weights[c_column]);
//					break;
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
	/*update the solution*/
	solution.updateSolution();
}

bool GRASP::repairing(Solution empty_solution, Solution& solution,vector <int> rep_columns){
	if (rep_columns.size() < 2) return false;
	/*use the list to uninstanciate the solution*/
	for (int i = 0 ; i < rep_columns.size() ; i++){
		if (solution.rep_solution[rep_columns[i]]==1){
			empty_solution.last_column = rep_columns[i];
			empty_solution.updateSolution();
		}
	}

	for (int i = 0 ; i < empty_solution.rowsCover.size() ; i++){
		int current_row = empty_solution.rowsCover[i].row;
		empty_solution.rowsCover[i].nb_covers = 0;
		empty_solution.rowsCover[i].col_covering.clear();
		int k = 0;
		for (int j = 0 ; j < problem.nb_columns ; j++){
			if ((k < rep_columns.size()-1) && (j == rep_columns[k]))
				k++;
			else if (problem.cover_matrix[current_row][j] == 1){
				empty_solution.rowsCover[i].nb_covers++;
				empty_solution.rowsCover[i].col_covering.push_back(j);
			}
		}
	}

	empty_solution.sorting();
	/*re-construct the solution*/
	while(!empty_solution.rowsCover.empty())
		construction(true,empty_solution);
	/*if the new solution if better than the previous one, replace it*/
	if (empty_solution.fitness < solution.fitness){
		copy_solution(empty_solution,solution);
		update_best_sol(solution);
		return true;
	}
	else
		return false;
}

void GRASP::penalty(Solution old_solution, Solution new_solution){
	for (int i = 0 ; i < old_solution.rep_solution.size() ; i++){
		if (new_solution.rep_solution[i] > old_solution.rep_solution[i])
			weights[i] = 1.1;
		if (new_solution.rep_solution[i] < old_solution.rep_solution[i])
			weights[i] = 1.1;
		if (new_solution.rep_solution[i] == 1 && old_solution.rep_solution[i] == 1)
			weights[i] = 0.8;
		if (new_solution.rep_solution[i]  == 0 && old_solution.rep_solution[i] == 0)
			weights[i] = 0.95;
	}
}

void GRASP::report(){
	cout << problem._input << " " <<  best_time<< " " << best_solution << endl;
}

void GRASP::update_best_sol(Solution solution){
	if (solution.fitness < best_solution){
		t_lastsol = clock();
		best_solution = solution.fitness;
		best_time = double(clock()-start_time) / CLOCKS_PER_SEC;
	}
}

pair<vector<int>,vector<int>> GRASP::divide_list(vector<int> input_list){
	pair<vector<int> , vector<int> > _new_lists;
	_new_lists.first.push_back(input_list[0]);
	_new_lists.first.push_back(input_list[1]);
	for (int i = 2 ; i <input_list.size() ; i++){
		if (rand()%2 != 0) _new_lists.first.push_back(input_list[i]);
		else _new_lists.second.push_back(input_list[i]);
	}
	return _new_lists;
}

void GRASP::init_lists(vector <vector <int> > & rep_lists, int nb_lists, Solution solution){
	vector<int> _aux;
	for (int i = 0 ; i < nb_lists ;i++)
		rep_lists.push_back(_aux);
	for (int i = 0 ; i < problem.nb_columns ; i++){
		if (solution.rep_solution[i] == 0)
			rep_lists[rand()%nb_lists].push_back(i);

	}
}


void GRASP::init_weights(){
	for (int i = 0 ; i < problem.nb_columns ; i++)
		weights.push_back(0);
}

void GRASP::copy_solution(Solution old_sol,Solution& new_sol){
	new_sol.fitness = old_sol.fitness;
	new_sol.last_column = old_sol.last_column;
	for (int i = 0 ;  i < new_sol.rep_solution.size() ; i++)
		new_sol.rep_solution[i] = old_sol.rep_solution[i];
}
