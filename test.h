#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <cstring>
#include "strings.h"
#include "timer.h"

using namespace std;

typedef struct {

	char a, b;

} ADD;

class TEST{

public:

	int n, *path, counter;
	double execution_time;

	STRINGS *opt; //save the optimal result
	STRINGS *old; //be passed previous result
	STRINGS *next; //save this iteration’s result and pass the result to next iteration
	STRINGS **temp; //save the temporary result for each k = 1, 2, ... , n
	ADD add[4];

	TEST(int);
	~TEST();

	void test_case();
	void find_OPT_Pair(void);
	void calculate_LCS(int k, const char *C, const char *D);
	void calculate_L(int k);
	void calculate_D(int k);
	void test_calculate_LCS();

};
