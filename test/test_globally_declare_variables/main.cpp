// main.cpp

//#include <stdio.h>
//#include<iostream>
#include "source.hpp"

//using namespace std;

int variable = 3;       // Define globally. Is now usable by source.
int main()
{
    cout << variable << endl;

    int variable = 5;   // Define locally (not visible to source).
    cout << variable << endl;
    func();

    variable = 8;
    cout << variable << endl;

    func();
	return variable;
}
