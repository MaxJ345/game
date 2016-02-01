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

	//roomDelete(starting_room_ptr, '\0');

    cout << endl;

    cout << starting_room_ptr->position.xcoord << ", " << starting_room_ptr->position.xcoord << endl;

    if(starting_room_ptr->south != NULL)
    {
        cout << "Address: " << starting_room_ptr << endl;
        cout << "Address: " << starting_room_ptr->south << endl;
        room * temp;
        cout << "Address: " << temp << endl;
        temp = starting_room_ptr->south;
        cout << "Address: " << temp << endl;
        cout << temp->position.xcoord << ", " << temp->position.ycoord << endl;

        starting_room_ptr = starting_room_ptr->south;
        cout << starting_room_ptr->position.xcoord << ", " << starting_room_ptr->position.ycoord << endl;
    }
}
