#include "strings.h"
#include <set>

STRINGS::STRINGS(int m){

		n = m;
		A = new char[n+1]; //from 0 to n, 0 ~ n-1 are real characters, n is '\0'
		B = new char[n+1];
		L_i = new int[n+1]; //from 0 to n, 0 is initial condition, 1 ~ n are real values for A[i-1] and B[j-1]
		L_j = new int[n+1];
		D_i = new int[n+1];
		D_j = new int[n+1];

		int i;

		//initialize L and D arrays
		for(i = 0; i < n+1; i++){

			L_i[i] = 0;
			L_j[i] = 0;
			D_i[i] = 0;
			D_j[i] = 0;
		}

		A[n] = '\0';
		B[n] = '\0';

		//The following will be used only when necessary
		l = 0, d = 0;

		L = (int**)malloc(sizeof(int*) * (n + 1));
		D = (int**)malloc(sizeof(int*) * (n + 1));
		A_Position = (int**)malloc(sizeof(int*) * (n + 1));
		B_Position = (int**)malloc(sizeof(int*) * (n + 1));

		for(i = 0; i < n + 1; i++) {

			L[i] = (int*)malloc(sizeof(int) * (n + 1));
			D[i] = (int*)malloc(sizeof(int) * (n + 1));
			A_Position[i] = (int*)malloc(sizeof(int) * (1 + 1));
			B_Position[i] = (int*)malloc(sizeof(int) * (1 + 1));
		}

}

STRINGS::STRINGS(int m, const string C, const string E){

	n = m;
	A = new char[n+1]; //from 0 to n, 0 ~ n-1 are real characters, n is '\0'
	B = new char[n+1];

	int i;

	for(i = 0; i < n+1; i++){

		A[i] = C[i];
		B[i] = E[i];
	}

	L_i = new int[n+1]; //from 0 to n, 0 is initial condition, 1 ~ n are real values for A[i-1] and B[j-1]
	L_j = new int[n+1];
	D_i = new int[n+1];
	D_j = new int[n+1];

	//initialize L and D arrays
	for(i = 0; i < n+1; i++){

		L_i[i] = 0;
		L_j[i] = 0;
		D_i[i] = 0;
		D_j[i] = 0;
	}

	A[n] = '\0';
	B[n] = '\0';

	//The following will be used only when necessary
	l = 0, d = 0;

	L = (int**)malloc(sizeof(int*) * (n + 1));
	D = (int**)malloc(sizeof(int*) * (n + 1));
	A_Position = (int**)malloc(sizeof(int*) * (n + 1));
	B_Position = (int**)malloc(sizeof(int*) * (n + 1));

	for(i = 0; i < n + 1; i++) {

		L[i] = (int*)malloc(sizeof(int) * (n + 1));
		D[i] = (int*)malloc(sizeof(int) * (n + 1));
		A_Position[i] = (int*)malloc(sizeof(int) * (1 + 1)); //0 and 1
		B_Position[i] = (int*)malloc(sizeof(int) * (1 + 1));
	}

}

STRINGS::~STRINGS(){

		int i;

		if(d > 0){

			for(i = 0; i < d; i++) delete[] D_LCS[i];
			free(D_LCS);
		}

		for(int i = 0; i < n+1; i++) {

			free(L[i]);
			free(D[i]);
			free(A_Position[i]);
			free(B_Position[i]);
		}

		free(L);
		free(D);
		free(A_Position);
		free(B_Position);

		delete[] A;
		delete[] B;
		delete[] L_i;
		delete[] L_j;
		delete[] D_i;
		delete[] D_j;

		//printf("STRINGS object has been flushed.\n");
}

void STRINGS::copy_STRINGS(STRINGS *s2){

		this->n = s2->n;

		for(int i = 0; i < this->n + 1; i++){

			this->A[i] = s2->A[i];
			this->B[i] = s2->B[i];
			this->L_i[i] = s2->L_i[i];
			this->L_j[i] = s2->L_j[i];
			this->D_i[i] = s2->D_i[i];
			this->D_j[i] = s2->D_j[i];

		} //for(i = 0; i < this->n + 1; i++)
}


void STRINGS::print_STRINGS(void){

	cout << "A: " << A << " , B: " << B << "; L: " << L_j[n] << ", D: " << D_j[n] << endl;

}

void STRINGS::calculate_full_L_and_D(void){

	int i, j;

	for(i = 0; i < n+1; i++){

		L[i][0] = 0;
		D[i][0] = 0;
	}

	for(j = 0; j < n+1; j++){

		L[0][j] = 0;
		D[0][j] = 0;
	}

	//i = k
	for(i = 1; i < n+1; i++)
		for(j = 1; j < n+1; j++){

		L[i][j] = max(L[i-1][j], L[i][j-1]); //at most one of S[i] and T[j] belongs to LCS

		if (A[i-1] == B[j-1]) L[i][j]  = max(L[i][j] , L[i-1][j-1] + 1); //both S[i] and T[j] belong to LCS

		}

	//i = k
	for(i = 1; i < n+1; i++)
		for(j = 1; j < n+1; j++){

			if(A[i-1] == B[j-1]){

				if(L[i][j] == 1) D[i][j] = 1; //S[i] and T[j] have one LCS
				else D[i][j] = D[i-1][j-1]; //the number of distinct occurrences of LCS remains the same
			}
			else {

				D[i][j] = 0; //otherwise initilaize D[i+1][j+1] to be zero

				if(L[i][j] == L[i-1][j]) D[i][j] = D[i][j] + D[i-1][j]; //add to the nunber if add S[i] and length remains the same
				if(L[i][j] == L[i][j-1]) D[i][j] = D[i][j] + D[i][j-1]; //add to the nunber if add T[j] and length remains the same
				if(L[i][j] == L[i-1][j-1])  D[i][j] = D[i][j] - D[i-1][j-1]; //add to the nunber if add T[j] and length remains the same
			}
		}
}

void STRINGS::print_full_L_and_D(void){

	int i, j;

	printf("L:\n");
	for (i = n; i >= 0; i--) {

			printf("[");
			for (j = 0; j <= n ; j++) {
				printf(" %d ", L[i][j]);
			}
			printf("]\n");
	}

	printf("\nD:\n");
	for (i = n; i >= 0; i--) {

			printf("[");
			for (j = 0; j <= n ; j++) {
				printf(" %d ", D[i][j]);
			}
			printf("]\n");
	}
}

void STRINGS::print_partial_L_and_D(void){

	int i;

	printf("L_i: [ ");
	for(i = 0; i < n+1; i++) printf("%d ", L_i[i]);
	printf("]\n");

	printf("L_j: [ ");
	for(i = n; i >= 0; i--) printf("%d ", L_j[i]);
	printf("]\n");

	printf("D_i: [ ");
	for(i = 0; i < n+1; i++) printf("%d ", D_i[i]);
	printf("]\n");

	printf("D_j: [ ");
	for(i = n; i >= 0; i--)  printf("%d ", D_j[i]);
	printf("]\n");

}

void STRINGS::print_Position_Matrix(void){

	int i, j;

	printf("\nA:\n");
	for (i = n; i >= 0; i--) {

			printf("[");
			for (j = 0; j <= 1 ; j++) {
				printf(" %d ", A_Position[i][j]);
			}
			printf("]\n");
	}

	printf("\nB:\n");
	for (i = n; i >= 0; i--) {

			printf("[");
			for (j = 0; j <= 1 ; j++) {
				printf(" %d ", B_Position[i][j]);
			}
			printf("]\n");
	}

}

void STRINGS::find_Distinct_LCS(void){

	int a, b;
	int i, j;

	//Step 1: re-build the reverse version, L[i][j], to facilitate the process
	for (i = n; i >= 0; i--) {
		for (j = n; j >= 0; j--) {
			if (i == n || j == n) L[i][j] = 0;
			else {

				L[i][j] = max(L[i+1][j], L[i][j+1]);

				if (A[i] == B[j]) L[i][j] = max(L[i][j], L[i+1][j+1] + 1);
			}
		}
	}

	for(i = n; i >= 0; i--){
		for(j = n; j >= 0; j--){
			if((i == n)||(j == n)) D[i][j] = 0;
			else{

				D[i][j] = 0;

				if(A[i] == B[j]){

					if(L[i][j] == 1) D[i][j] = 1;
					else D[i][j] = D[i+1][j+1]; //because ai = bj, distinct LCS # will remain the same

				} //if(A[i] == B[j])
				else{ //if(A[i] != B[j])

					//according to previous count, decide D[i][j]
					if(L[i][j] == L[i+1][j]) D[i][j] = D[i][j] + D[i+1][j];
					if(L[i][j] == L[i][j+1]) D[i][j] = D[i][j] + D[i][j+1];
					if(L[i][j] == L[i+1][j+1]) D[i][j] = D[i][j] - D[i+1][j+1];

				} //else of if(A[i] == B[j])
			} //else of if((i == n)||(j == n))
		} //for(j = n; j >= 0; j--)
	} //for(i = n; i >= 0; i--)

	//Step 2: build position matrices for 0 and 1 (preprocessing of finding Distinct LCS's)

	//A_Position[i][0] means the position of the first 0 in the last i characters of A
	//B_Position[i][0] means the position of the first 0 in the last i characters of B
	//A_Position[i][1] means the position of the first 1 in the last i characters of A
	//B_Position[i][1] means the position of the first 1 in the last i characters of B

	for (i = 0; i < 2; i++) {

		A_Position[n][i] = n;
		B_Position[n][i] = n;
	}

	for (i = n-1; i >= 0; i--){
		for (j = 0; j < 2; j++) {

			a = (int)(A[i] - '0');

			if (a == j) {
				A_Position[i][j] = i;
			}
			else {
				A_Position[i][j] = A_Position[i+1][j];
			}

			b = (int)(B[i] - '0');

			if (b == j) {
				B_Position[i][j] = i;
			}
			else {
				B_Position[i][j] = B_Position[i+1][j];
			}
		} //for (j = 0; j < 2; j++)
	} //for (i = n-1; i >= 0; i--)

	//print_Position_Matrix();

	l = L[0][0], d = D[0][0];

	if(l==0 || d == 0) return;

	char *D_LCS_1;
	D_LCS_1 = new char[l+1];

	D_LCS = (char**)malloc(sizeof(D_LCS_1) * d);

	delete[] D_LCS_1;

	for(i = 0; i < d; i++){

		D_LCS[i] = new char[l+1];

		for(j = 0; j < l; j++) D_LCS[i][j] = '0';
		D_LCS[i][l] = '\0';
	}

	bool *path;
	int *i_start, *j_start;

	path = new bool[l+1];
	i_start = new int[l+1];
	j_start = new int[l+1];

	char **temp; //save the temporary result for each k = 1, 2, ... , n

	char *temp_1;
	temp_1 = new char[l+1]; //used to indicate the size of an object

	temp = (char **)malloc(sizeof(temp_1) * (l + 1));

	delete[] temp_1;

	for(i = 0; i < l + 1; i++){

		temp[i] = new char[l+1];
		for(j = 0; j < l; j++) temp[i][j] = '0';
		temp[i][l] = '\0';
		path[i] = 0;
		i_start[i] = 0;
		j_start[i] = 0;
	}

	path[1] = 0;
	int p = 0; //Distinct LCS counter

	find_Distinct_LCS_2(path, temp, i_start, j_start, 1, p);

	for(i = 0; i < l + 1; i++){

		delete[] temp[i];
	}

	free(temp);

	delete[] path;
	delete[] i_start;
	delete[] j_start;

}

void STRINGS::find_Distinct_LCS_2(bool *path, char **temp, int* i_start, int* j_start, int k, int &p){ //use DFS tree; cannot claim any variable in this recursive function!!!

		int i, j;
		int a, b, q;

		strncpy(D_LCS[p], temp[k-1], l+1);
		i = i_start[k-1];
		j = j_start[k-1];
		q = path[k];

		a = A_Position[i][q];
		b = B_Position[j][q];

		//printf("k %d, q %d, i %d, j %d, a %d, b %d\n", k, q, i, j, a, b);

		if(L[a][b] == l - (k-1)){

			if(q == 0) D_LCS[p][k-1] = '0';
			else if(q == 1) D_LCS[p][k-1] = '1';
			else printf("Error\n");

			//cout << "LCS #" << p << " " << distinct_LCS[p].subsequence << " with length " << k << endl;

			strncpy(temp[k], D_LCS[p], l+1);
			i_start[k] = a + 1;
			j_start[k] = b + 1;

			if(k < l){

				k = k + 1;
				path[k] = 0;

				find_Distinct_LCS_2(path, temp, i_start, j_start, k, p);

			}
			else{

				if(k == l){

					//cout << "LCS #" << p << " " << distinct_LCS[p].subsequence << " with length " << k << " completed!" << endl;

					p = p + 1;

					if(p == d) return;
				}

				while(path[k] + 1 > 1){ //find the node which is not yet explored

					k = k - 1;
				}

				path[k] = path[k] + 1; //explore other sibling nodes

				find_Distinct_LCS_2(path, temp, i_start, j_start, k, p);
			}

		}
		else{

			while(path[k] + 1 > 1){ //find the node which is not yet explored

				k = k - 1;
			}

			path[k] = path[k] + 1; //explore other sibling nodes

			find_Distinct_LCS_2(path, temp, i_start, j_start, k, p);
		}

}

void STRINGS::print_Distinct_LCS(void){

	for(int k = 0; k < d; k++) cout << "    #" << (k+1) << " " << D_LCS[k] << endl;

}







