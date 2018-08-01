/*
 * Set Covering problem
 *
 * Author: 			Victor Reyes
 * University:  	Pontificia Universidad Catolica de Valparaiso, Valparaiso, Chile
 * Created		:	August 1th 2018
 * Last Update:   	August 1th 2018
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include <SCP.h>

using namespace std;

int main(int argc, char** argv){

    if (argc<4) {
    	cerr << "You must use : ./SCP-GRASP ./benchs/scpxx.txt MAX_TIME SEED";
    	exit(1);
    }

	double start_s;
    /*Input reading*/
	SCP problem(argv[1]);

	return 0 ;
}
