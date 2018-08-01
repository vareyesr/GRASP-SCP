/*
 * SCP.cpp
 *
 * Author: 			Victor Reyes
 * University:  	Pontificia Universidad Catolica de Valparaiso, Valparaiso, Chile
 * Created		:	August 1th 2018
 * Last Update:   	August 1th 2018
 */

#include <SCP.h>

SCP::SCP(std::string inputfileName): _input(inputfileName),nb_rows(0),nb_columns(0){
	read_file(_input);
}

void SCP::read_file(std::string input){

	std::ifstream file;
	file.open(input);
	file >> nb_rows;
	file >> nb_columns;

	/*storing cost vector*/
	for (int i = 0 ; i < nb_columns ; i++){
		double _aux;
		file >> _aux;
		cost_vector.push_back(_aux);
	}
	/*storing input matrix*/
	for (int i = 0 ; i < nb_rows ; i++){
		vector<int> _aux;
		cover_matrix.push_back(_aux);
		for (int j = 0 ; j < nb_columns ; j++){
			int _element;
			//file >> _element;
			_element = 0;
			cover_matrix[i].push_back(_element);
		}
	}
	for (int i = 0 ; i < nb_rows ; i ++){
		int nb_ones;
		int column_one;
		file >> nb_ones;
		for (int j = 0 ; j < nb_ones ; j++){
			file >> column_one;
			cover_matrix[i][column_one-1] = 1;
		}

	}
}
