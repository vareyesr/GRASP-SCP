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

class SCP {
private:
    std::string _input;
public:
	SCP(std::string inputFileName);
	/*number of rows in A*/
	int nb_rows;
	/*number of columns in A*/
	int nb_columns;
	/*cost vector*/
	std::vector<double> cost_vector;
	/*input matrix*/
	std::vector<std::vector<int>> ctrs;


	void read_file(std::string input);
};



#endif /* SRC_SCP_H_ */
