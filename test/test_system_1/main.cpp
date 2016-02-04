// main.cpp

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "roomGen.hpp"
#include "roomDelete.hpp"

int main(void)
{
	srand(time(NULL));
	room * starting_room_ptr = roomGen(NULL, 1, '\0');

	roomDelete(starting_room_ptr, '\0');



}
