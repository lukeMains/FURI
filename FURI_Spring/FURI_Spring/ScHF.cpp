#include "ScHF.h"
#include <stdlib.h>
#include <iostream>
#include <ctime>


//Generates a random ScHF each time
ScHF::ScHF(int N, int k, int v, int w, int t) {
	this->N = N;
	this->k = k;
	this->v = v;
	this->w = w;
	this->t = t;

	this->scattering = true;

	//Setup Column Vector
	for (int i = 0; i < k; ++i) {
		column_vector.push_back(i);
	}

	/*
	//Use this code for building random array all at once
	//Allocate space for Array
	Array = (int **)malloc(N * sizeof(int *));
	for (int i = 0; i < N; i++) {
		Array[i] = (int *)malloc(k * sizeof(int));
	}

	//Build random 2D array
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < k; j++) {
			int value = rand() % v;
			Array[i][j] = value;
			value++;
		}
	}
	*/
	
	//Use this code when building homogeneous array row by row.
	int* symbolSet = (int*)malloc(v * sizeof(int));
	int lowerBound = floor((double)k / v);
	int upperBound = ceil((double)k / v);

	Array = (int **)malloc(N * sizeof(int *));
	for (int i = 0; i < N; i++) {
		Array[i] = (int *)malloc(k * sizeof(int));

		for (int l = 0; l < v; l++) {
			symbolSet[l] = 0; //Start at 0 and count up to the bound values
		}

		//Build a row, check homogeneous, repeat.
		for (int j = 0; j < k; j++) {
			int value = rand() % v;

			for (int max_loops = 0; symbolSet[value] >= lowerBound && max_loops < 200; max_loops++) {
				value = rand() % v;
			}

			for (int count = 0; count < v - 1; count++) {
				if (symbolSet[value] + 1 > upperBound) {
					value = (value + 1) % v;
				}
			}

			Array[i][j] = value;

			symbolSet[value]++;
		}
	}
	
}

void ScHF::printScHF() {
	cout << "[";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < k; j++) {
			cout << Array[i][j] << " ";
		}

		if (i == N - 1) {
			cout << "]\t";
		}
		else {
			cout << "| \n|";
		}
	}
}

bool ScHF::isHomogeneous() {
	bool homogeneous = true;
	int lowerBound = floor((double)k / v);
	int upperBound = ceil((double)k / v);

	for (int row = 0; row < N; row++) {
		int symbol_count = 0;	//Will keep track of the count of a certain symbol to compare to w.
		int vPrime = 0;			//vPrime is a symbol in set V

		while (vPrime < v && homogeneous) {
			for (int column = 0; column < k; column++) {
				if (vPrime == Array[row][column]) {
					symbol_count++;
				}
			}

			if (symbol_count <  lowerBound || symbol_count > upperBound) {
				homogeneous = false;
			}

			vPrime++;
			symbol_count = 0;
		}
	}

	return homogeneous;
}

void ScHF::isScattering(int offset, int k) {
	if (k == 0) {
		if (checkSubArray(column_vector_subset)) {
			return;
		}
		else {
			scattering = false;
			return;
		}
	}
	for (int i = offset; i <= column_vector.size() - k; ++i) {
		column_vector_subset.push_back(column_vector[i]);
		isScattering(i + 1, k - 1);
		column_vector_subset.pop_back();
	}
}

bool ScHF::checkSubArray(vector<int> column_vector_subset) {
	bool output = false;

	for (int row = 0; row < N; row++) {
		int count = 0;					//Will keep track of the count of a certain symbol to compare to w.
		int vPrime = 0;					//vPrime is a symbol in set V
		int uniqueRowCount = 0;			//Must be greater than or equal to 1 for sub-array to qualify.
		bool isUniqueRow = false;

		while (!isUniqueRow) {
			for (int j = 0; j < column_vector_subset.size(); j++) {
				if (Array[row][column_vector_subset[j]] == vPrime) {
					count++;
				}
			}

			if (count > w) {
				break;		//There was too many symbols and the row does not qualify.
			}
			else if (vPrime >= v) { //If vPrime is v, then the loop is finished.
				isUniqueRow = true;
				uniqueRowCount++;
				break;
			}
			else {
				count = 0;
				vPrime++;
			}
		}

		if (uniqueRowCount >= 1) {
			output = true;
			row = N;
		}
	}

	//Be able to check which subset of columns cause problems.
	/*if(output == false){
	cout << "Columns: " << ": [ ";
	for (int i = 0; i < column_vector_subset.size(); i++) {
	cout << column_vector_subset[i] << " ";
	}
	cout << "]" << endl;

	//Print the sub-array causing problems.
	cout << "\t[";
	for (int i = 0; i < N; i++) {
	for (int j = 0; j < column_vector_subset.size(); j++) {
	cout << Array[i][column_vector_subset[j]] << " ";
	}

	if (i == N - 1) {
	cout << "]\n\n";
	}
	else {
	cout << "| \n\t|";
	}
	}
	}*/

	return output;
}


