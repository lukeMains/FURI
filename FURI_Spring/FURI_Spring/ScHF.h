#pragma once
#ifndef ScHF_H_
#define ScHF_H_

#include <vector>

using namespace std;


class ScHF {
private:

public:
	int N; //Rows
	int k; //Columns
	int v; //Set of Symbols
	int w; //Allowed number of repeated symbols (1 for PHF)
	int t; //Number of columns in the sub-array which must have a unique row.
	int **Array; //Pointer to the actual scattering hash family.

	bool scattering;
	vector<int> column_vector; //Used for keeping track of the subset of t columns when checking the scattering property.
	vector<int> column_vector_subset;

	//Constructor
	ScHF(int N, int k, int v, int w, int t);	

	//Methods
	void printScHF();
	bool isHomogeneous();
	void isScattering(int offset, int k);
	bool checkSubArray(vector<int> column_vector_subset);
};

#endif // ScHF_H_