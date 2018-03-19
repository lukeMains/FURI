/*
Author: Luke Mains
*/

#include "ScHF.h"
#include <stdlib.h>
#include <cstdio>
#include <ctime>
#include <vector>

using namespace std;

int main() {
	srand(time(NULL)); //Seed for random number generation.
	FILE *file = fopen("./FURI_Data/newData.csv", "w");
	if (!file) {
		perror("File opening failed");
		return EXIT_FAILURE;
	}

	int N = 10;
	int k = 20;
	int v = 4;
	int w = 2;
	int t = 5;
	int scount = 0;
	int hcount = 0;

	ScHF *hashFam;

	fprintf(file, "N,k,v,w,t,Scattering Count,Trials\n");

	//Rows
	for (int b = 10; b < 15; b++) {
		//Number of Symbols
		for (int c = 2; c <= 5; c++) {
			//Scattering parameter
			for (int d = 1; d <= 3; d++) {
				//Number of columns in a subset
				for (int e = d + 1; e <= 5; e++) {
					for (int i = 0; i < 200; i++) {
						hashFam = new ScHF(b, c*d, c, d, e);
						hashFam->isScattering(0, e);
						if (hashFam->scattering) {
							scount++;
						}
					}
					printf("Size: %d by %d. Correct: %d\n", N, k, scount);
					fprintf(file, "%d,%d,%d,%d,%d,%d,%d\n", b, c*d, c, d, e, scount, 200);
					scount = 0;
				}
			}
		}
	}
	

	fclose(file);

}














	/* Old Runs
	//-------Scattering Data-----------
	//Columns
	//for (int a = 20; a < 25; a++) {
		int a = 21;
		//Rows
		//for (int b = 10; b < 15; b++) {
			int b = 7;
			//Number of Symbols
			for (int c = 2; c <= 5; c++) {
				//Scattering parameter
				for (int d = 1; d <= 3; d++) {
					//Number of columns in a subset
					for (int e = d+1; e <= 5; e++) {
						for (int i = 0; i < 200; i++) {
							hashFam = new ScHF(b, a, c, d, e);
							hashFam->isScattering(0, e);
							if (hashFam->scattering) {
								scount++;
							}
						}
						printf("Size: %d by %d. Correct: %d\n", N, k, scount);
						fprintf(file, "%d,%d,%d,%d,%d,%d,%d\n", b, a, c, d, e, scount, 200);
						scount = 0;
					}
				}
			}
		//}
	//}
	//-------End Scattering Data-----------
	

	//-------Homogeneous Data--------------
	//Columns
	for (int a = 10; a < 40; a = a+2) {
		//Rows
		for (int b = 2; b < 30; b++) {
			//Number of Symbols
			//for (int c = 2; c <= 5; c++) {
			int c = 2;
				//Scattering parameter
				//for (int d = 1; d <= 3; d++) {
				int d = 1;
					//Number of columns in a subset
					//for (int e = d + 1; e <= 5; e++) {
					int e = 2;
						for (int i = 0; i < 1000; i++) {
							hashFam = new ScHF(b, a, c, d, e);
							if (hashFam->isHomogeneous()) {
								hcount++;
							}
						}
						printf("Size: %d by %d. Correct: %d\n", a, b, hcount);
						fprintf(file, "%d,%d,%d,%d,%d,%d,%d\n", b, a, c, d, e, hcount, 1000);
						hcount = 0;
					//}
				//}
			//}
		}
	}
	//-------End Homogeneous Data---------- */
	
	








	//-------------------------Tests-----------------------------------------------
	//-----------------------------------------------------------------------------

	//Testing isScattering() method
	/*int count = 0;
	hashFam = new ScHF(N, k, v, w, t);
	hashFam->isScattering(0, t);

	//while (hashFam->scattering && count < 200) {
	for (int i = 0; i < 100; i++) {
		hashFam = new ScHF(N, k, v, w, t);
		//hashFam->printScHF();
		//printf("\n\n");
		hashFam->isScattering(0, t);
		//printf("\nOverall: %s\n", hashFam->scattering ? "true" : "false");
		if (hashFam->scattering) {
			count++;
		}
	}
	//}

	//printf("\n\n");
	//hashFam->printScHF();
	printf("\n\nTrials: %d/200 or %f%%\n\n", count, (float)count/200);*/

	// Check homogeneous test
	/*for (int j = 2; j < 6; j++) {
		int homoCount = 0;
		for (int i = 0; i < 100000; i++) {
			hashFam = new ScHF(j, 12, 2, 1, 2);

			if (hashFam->isHomogeneous()) {
				homoCount++;
			}
		}
		printf("%f%\n", (float)homoCount / 1000);
	}*/

	//-------------------------------------------------------------------------