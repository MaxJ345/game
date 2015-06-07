#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

void test_function(int seed)
{
	srand(time(NULL));

    cout << "Current seed: " << seed << endl;

	if(rand() % seed == 0)
		test_function(++seed);					// notice how it is '++seed', and not 'seed++'; that is what makes it work, and that is why the original code ran for too long 
}

int main(void)
{
	test_function(1);
}
