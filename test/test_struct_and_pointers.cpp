// This code is just for testing the room struct and how pointers work. It's more of a refresher for myself.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct room {
	int number;
	struct room * north;
	struct room * south;
	struct room * east;
	struct room * west;
} ;

int main(void)
{
	room * room1_ptr = new room;
	room * room2_ptr = new room;

	room1_ptr->number = 3;

	cout << room1_ptr->number;

	room2_ptr->north = room1_ptr;

	cout << room2_ptr->north->number;

	return 0;
}
