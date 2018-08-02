/*
 * SCP-utils.cpp
 *
 * Author: 			Victor Reyes
 * University:  	Pontificia Universidad Catolica de Valparaiso, Valparaiso, Chile
 * Created		:	August 2th 2018
 * Last Update:   	August 2th 2018
 */

#include <SCP-utils.h>



void rowDomination(const SCP problem, Solution solution){

	int nb_dominated = 0;
	for (int i = 0 ; i < solution.rowsCover.size(); i++){
		if (solution.rowsCover[i].nb_covers > 1)
			break;
		else
			nb_dominated++;
	}
	for (int i = 0 ; i < nb_dominated ; i++){
		solution.last_column = solution.rowsCover[i].col_covering[0];
		solution.updateSolution();
	}

};

