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
}
