#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct room {
	int number;				// content
	struct room * north;
	struct room * south;
	struct room * east;
	struct room * west;
} ;

room * roomGen(int input)
{
    room * room_ptr = new room;
    room_ptr->number = rand();

    cout << room_ptr->number << endl;

    return room_ptr;
}

int main(void)
{
    srand(time(NULL));

    room * room_ptr = roomGen(4);
    cout << room_ptr->number << endl;

    room * north_room_ptr = roomGen(4);
    cout << north_room_ptr->number << endl;

    room_ptr->north = north_room_ptr;
    cout << room_ptr->north->number << endl;

    room * south_room_ptr = roomGen(4);
    cout << south_room_ptr->number << endl;

    room_ptr->south = south_room_ptr;
    cout << room_ptr->south->number << endl;

    room * east_room_ptr = roomGen(4);
    cout << east_room_ptr->number << endl;

    room_ptr->east = east_room_ptr;
    cout << room_ptr->east->number << endl;

    return 0;
}
