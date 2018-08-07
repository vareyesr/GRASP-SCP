/*
 * SCP.h
 *
 * Author: 			Victor Reyes
 * University:  	Pontificia Universidad Catolica de Valparaiso, Valparaiso, Chile
 * Created		:	August 1th 2018
 * Last Update:   	August 1th 2018
 */

#ifndef SRC_SCP_H_
#define SRC_SCP_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class SCP {
public:
    std::string _input;
	SCP(std::string inputFileName);
	/*number of rows in A*/
	int nb_rows;
	/*number of columns in A*/
	int nb_columns;
	/*cost vector*/
	vector <double> cost_vector;
	/*input matrix*/
	vector<vector<int>> cover_matrix;
	/**/
	void read_file(std::string input);

};



#endif /* SRC_SCP_H_ */
