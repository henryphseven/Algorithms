#include "test.h"

TEST::TEST(int m){

	n = m;

	opt = new STRINGS(n); //save the optimal result
	old = new STRINGS(n); //be passed previous result
	next = new STRINGS(n); //save this iteration’s result and pass the result to next iteration
	path = new int[n+1];

	STRINGS *temp_1;
	temp_1 = new STRINGS(n); //used to indicate the size of an object

	temp = (STRINGS **)malloc(sizeof(temp_1) * (n+1));

	delete temp_1;

	for(int i = 0; i < n+1; i++){

		temp[i] = new STRINGS(n);
		path[i] = 0;
	}

	add[0].a = '0';
	add[0].b = '0';

	add[1].a = '0';
	add[1].b = '1';

	add[2].a = '1';
	add[2].b = '0';

	add[3].a = '1';
	add[3].b = '1';

	counter = 0;

	execution_time = 0;

}

TEST::~TEST(){

	delete opt;
	delete old;
	delete next;
	delete[] path;

	for(int i = 0; i < n+1; i++){

		delete temp[i];
	}

	free(temp);

	//printf("TEST object has been flushed.\n");
}

void TEST::test_case(){

	start_timer(); //initiate the timer

	find_OPT_Pair();

	opt->find_Distinct_LCS();

	execution_time = elapsed_time(); //the functions return units of seconds

	////////////////////The following is for debug//////////////////////////////
	printf("\nThe following message is for debug purpose:\n");
	printf("When n = %d, total number of string pairs explored is %d\n", n, counter);
	printf("\n");

	////////////////////The following is the required output////////////////////
	printf("Output produced by the execution of our program for n = %d:\n\n", n);

	printf("(1) the determined binary strings A and B:\n");
	cout << "    A: " << opt->A << endl;
	cout << "    B: " << opt->B << endl << endl;

	printf("(2) the number of distinct LCS's:\n");
	cout << "    " << opt->D_j[n] << endl << endl;

	printf("(3) the list of those LCS's:\n");
	opt->print_Distinct_LCS();

	printf("\n(4) the number of seconds of execution time:\n");
	printf("    %.2lf\n\n", execution_time);

}

void TEST::test_calculate_LCS(){

	for(int k = 1; k < n+1; k++){

		old->copy_STRINGS(next); //re-use the previous result
		calculate_L(k);
		calculate_D(k);
		next->print_partial_L_and_D();

	}
}

void TEST::calculate_LCS(int k, const char *C, const char *D){ //use DFS tree; cannot claim any variable in this recursive function!!!

				next->copy_STRINGS(temp[k-1]); //k = 1, q_counter[0] = 0

				old->copy_STRINGS(next); //re-use the previous result

				next->A[k-1] = add[path[k]].a; //try another addition combination
				next->B[k-1] = add[path[k]].b;

				calculate_L(k);
				calculate_D(k);

				temp[k]->copy_STRINGS(next);

				if(k < n){

					k = k + 1;

					path[k] = 0; ////explore the left child first

					calculate_LCS(k, C, D);

				}
				else{

					counter++;

					//cout << "#" << counter << " ";
					//next->print_STRINGS();
					//next->print_partial_L_and_D();

					if(next->D_j[n] > opt->D_j[n]) { //compare # of distinct LCS's

							opt->copy_STRINGS(next);
					}

					if(strcmp(next->A, C) == 0 && strcmp(next->B, D) == 0) return;

					while(path[k] + 1 > 3){ //find the node which is not yet explored

						k = k - 1;
					}

					path[k] = path[k] + 1; //explore other sibling nodes

					calculate_LCS(k, C, D);

				} //else of if(k < n)
}

void TEST::find_OPT_Pair(void){

	if(n <= 7) {

		char *C;
		C = new char[n+1];

		for(int i = 0; i < n; i++) C[i] = '1';
		C[n] = '\0';

		path[1] = 0;

		calculate_LCS(1, C, C);

		delete[] C;
	}
	else{

		int i, j, k, l, m, o, p;

		for(i = 0; i < 2; i++)
			for(j = 0; j < 4; j++)
				for(k = 0; k < 4; k++)
					for(l = 0; l < 4; l++)
						for(m = 0; m < 4; m++){

							char *C, *D;
							C = new char[n+1];
							D = new char[n+1];

							next->A[0] = add[i].a;
							next->B[0] = add[i].b;

							next->A[1] = add[j].a;
							next->B[1] = add[j].b;

							next->A[2] = add[k].a;
							next->B[2] = add[k].b;

							next->A[3] = add[l].a;
							next->B[3] = add[l].b;

							next->A[4] = add[m].a;
							next->B[4] = add[m].b;

							for(p = 1; p < 6; p++){

								old->copy_STRINGS(next); //re-use the previous result
								calculate_L(p);
								calculate_D(p);
							}

							temp[5]->copy_STRINGS(next);

							stpcpy(C, temp[5]->A);
							stpcpy(D, temp[5]->B);

							for(o = 5; o < n; o++) {
								C[o] = '1';
								D[o] = '1';
							}
							C[n] = '\0';
							D[n] = '\0';

							path[6] = 0;

							calculate_LCS(6, C, D);

							delete[] C;
							delete[] D;

						}
	}

}

void TEST::calculate_L(int k){ //k = 2 => A, B is 1 (start from 0); L, D is 2 (start from 1 except initial condition)

	//initialize L_i, L_j
	next->L_i[0] = 0;
	next->L_j[0] = 0;

	//i = k
	for(int j = 1; j < k; j++){

		next->L_i[j] = max(old->L_i[j], next->L_i[j-1]); //at most one of S[i] and T[j] belongs to LCS

		if (next->A[k-1] == next->B[j-1]) next->L_i[j]  = max(next->L_i[j] , old->L_i[j-1] + 1); //both S[i] and T[j] belong to LCS

	}

	//j = k
	for(int i = 1; i < k; i++){

		next->L_j[i] = max(old->L_j[i], next->L_j[i-1]); //at most one of S[i] and T[j] belongs to LCS

		if (next->A[i-1] == next->B[k-1]) next->L_j[i]  = max(next->L_j[i] , old->L_j[i-1] + 1); //both S[i] and T[j] belong to LCS

	}

	next->L_j[k] = max(next->L_i[k-1], next->L_j[k-1]); //at most one of S[i] and T[j] belongs to LCS

	if (next->A[k-1] == next->B[k-1]) next->L_j[k]  = max(next->L_j[k] , old->L_j[k-1] + 1); //both S[i] and T[j] belong to LCS

	next->L_i[k] = next->L_j[k];

}

void TEST::calculate_D(int k){ //k = 2 => A, B is 1 (start from 0); L, D is 2 (start from 1 except initial condition)

	//initialize D_i, D_j
	next->D_i[0] = 0;
	next->D_j[0] = 0;

	//i = k
	for(int j = 1; j < k; j++){ //D represents # of distinct LCS's

		if(next->A[k-1] == next->B[j-1]){

			if(next->L_i[j] == 1) next->D_i[j] = 1; //S[i] and T[j] have one LCS
			else next->D_i[j] = old->D_i[j-1]; //the number of distinct occurrences of LCS remains the same

		}
		else {

			next->D_i[j] = 0; //otherwise initilaize D[i+1][j+1] to be zero

			if(next->L_i[j] == old->L_i[j]) next->D_i[j] = next->D_i[j] + old->D_i[j]; //add to the nunber if add S[i] and length remains the same
			if(next->L_i[j] == next->L_i[j-1]) next->D_i[j] = next->D_i[j] + next->D_i[j-1]; //add to the nunber if add T[j] and length remains the same
			if(next->L_i[j] == old->L_i[j-1])  next->D_i[j] = next->D_i[j] - old->D_i[j-1]; //add to the nunber if add T[j] and length remains the same
		}
	}

	//j = k
	for(int i = 1; i < k; i++){

		if(next->A[i-1] == next->B[k-1]){

			if(next->L_j[i] == 1) next->D_j[i] = 1; //S[i] and T[j] have one LCS
			else next->D_j[i] = old->D_j[i-1]; //the number of distinct occurrences of LCS remains the same

		}
		else {

			next->D_j[i] = 0; //otherwise initilaize D[i+1][j+1] to be zero

			if(next->L_j[i] == old->L_j[i]) next->D_j[i] = next->D_j[i] + old->D_j[i]; //add to the nunber if add S[i] and length remains the same
			if(next->L_j[i] == next->L_j[i-1]) next->D_j[i] = next->D_j[i] + next->D_j[i-1]; //add to the nunber if add T[j] and length remains the same
			if(next->L_j[i] == old->L_j[i-1])  next->D_j[i] = next->D_j[i] - old->D_j[i-1]; //add to the nunber if add T[j] and length remains the same
		}
	}

	if(next->A[k-1] == next->B[k-1]){

		if(next->L_j[k] == 1) next->D_j[k] = 1; //S[i] and T[j] have one LCS
		else next->D_j[k] = old->D_j[k-1]; //the number of distinct occurrences of LCS remains the same

	}
	else {

		next->D_j[k] = 0; //otherwise initilaize D[i+1][j+1] to be zero

		if(next->L_i[k] == next->L_i[k-1]) next->D_j[k] = next->D_j[k] + next->D_i[k-1]; //add to the nunber if add S[i] and length remains the same
		if(next->L_j[k] == next->L_j[k-1]) next->D_j[k] = next->D_j[k] + next->D_j[k-1]; //add to the nunber if add T[j] and length remains the same
		if(next->L_j[k] == old->L_j[k-1])  next->D_j[k] = next->D_j[k] - old->D_j[k-1]; //add to the nunber if add T[j] and length remains the same
	}

	next->D_i[k] = next->D_j[k];

}



