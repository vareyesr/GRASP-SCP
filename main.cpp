/*
 * Set Covering problem
 *
 * Author: 			Victor Reyes
 * University:  	Pontificia Universidad Catolica de Valparaiso, Valparaiso, Chile
 * Created		:	August 1th 2018
 * Last Update:   	August 6th 2018
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include <SCP.h>
#include <GRASP.h>
#include <Solution.h>

using namespace std;

int main(int argc, char** argv){

    if (argc<4) {
    	cerr << "You must use : ./SCP-GRASP ./benchs/scpxx.txt MAX_TIME SEED";
    	exit(1);
    }
	double start_time;
    /*Input reading*/
	SCP problem(argv[1]);
	/*Set parameters of search*/
    double MAX_TIME = atoi(argv[2]);			/*Input: MAX execution time*/
    int random_seed = atoi(argv[3]);            /*Input: Random seed*/

    std::srand(random_seed);

    /*solution creation*/
    Solution solution(problem);


    /*Init the solution with the preprocessing*/
    //solution.rowDomination();
    /*Apply the GRASP strategy*/

    GRASP _algorithm(problem,solution,MAX_TIME);
    _algorithm.search();
    /*print the best solution + time*/
    _algorithm.report();
    return 0 ;
}
