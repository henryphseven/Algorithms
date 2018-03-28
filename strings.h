#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <cstring>
#define STRING_LENGTH 15

using namespace std;

class STRINGS{

public:

	int n;
	char *A, *B;
	int *L_i, *L_j, *D_i, *D_j;
	int l, d;
	int **L, **D, **A_Position, **B_Position;
	char **D_LCS;

	STRINGS(int);
	STRINGS(int, const string, const string);
	~STRINGS();

	void copy_STRINGS(STRINGS *s2);
	void print_STRINGS(void);

	void calculate_full_L_and_D(void);
	void print_full_L_and_D(void);
	void print_partial_L_and_D(void);
	void print_Distinct_LCS(void);
	void print_Position_Matrix(void);

	void find_Distinct_LCS(void);
	void find_Distinct_LCS_2(bool *path, char **temp, int* i_start, int* j_start, int k, int &p);

};




