/*
 * rowCovering.cpp
 *
 *  Created on: Aug 2, 2018
 *      Author: victor
 */

#include <rowCovering.h>


rowCovering::rowCovering(const SCP problem,int row): problem(problem),row(row),nb_covers(0){

	searchRows();

}


void rowCovering::searchRows(){

	for (int j = 0 ; j < problem.nb_columns ; j++)
	if (problem.cover_matrix[row][j]==1){
		nb_covers++;
		col_covering.push_back(j);
	}
}
