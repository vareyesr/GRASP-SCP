/*
 * rowCovering.h
 *
 *  Created on: Aug 2, 2018
 *      Author: victor
 */

#ifndef SRC_ROWCOVERING_H_
#define SRC_ROWCOVERING_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <SCP.h>

using namespace std;

class rowCovering{
public:
	rowCovering(const SCP problem,int row);

	int row;
	int nb_covers;
	std::vector<int> col_covering;

	void searchRows(const SCP problem);
};


#endif /* SRC_ROWCOVERING_H_ */
