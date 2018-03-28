#include "test.h"

using namespace std;

int main(int argc, char *argv[])
{
	TEST test1(4);
	test1.test_case();

	TEST test2(7);
	test2.test_case();

	TEST test3(10);
	test3.test_case();

	TEST test4(12);
	test4.test_case();

	return 0;
}

/*
STRINGS test(10, "0101010101", "1001100110");
test.calculate_full_L_and_D();
test.print_full_L_and_D();
test.find_Distinct_LCS();
test.print_Distinct_LCS();
*/
