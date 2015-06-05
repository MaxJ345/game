/*
This function is called upon to recursively generate rooms. It will generate rooms to the North, South, East, and West of the current room. 
The inputs are the pointer for the current room (should be NULL initially), a seed for random generation , and a coordinate for reference (not used for the initial value).
The value returned by this function will be a pointer to the first room created. This should give the user access to the entire complex.
NOTE: The current version of the code does not take into account that rooms are generated without regard for each other's locations; if a 2-D grid/map was drawn of the complex, there might (and probably will) be rooms that are overlapping (take up the same spot). This doesn't break the code (these rooms will always have unique spaces allocated in memory), but it makes it confusing for the user. A way around this would be to implement a grid system that checks the location of a room before it is allocated/created.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

room * roomGen(* room_ptr, int selection_seed, char coord)
{
	char coordinate[4] = {'N', 'S', 'E', 'W'};
	char coordinate_opposite[4] = {'S', 'N', 'W', 'E'};
	srand(time(NULL));
	
	if(room_ptr == NULL)			// base case
	{
		initial_ptr = new room;

		// this sets which "doors will be opened" (which rooms will be created) using a seed initialized by the user
		for(int i=0; i<4; i++)
		{
			if(rand() % selection_seed == 0)
				roomGen(initial_ptr, selection_seed++, coordinate[i]);
		}
	}
	
	else							// recursion; note that recursion is stopped by the fact that the probability of creating a new room gets smaller as recursion gets deeper
	{
		temp_room_ptr = new room;
		
		// set correct direction for pointer from original room to new room, and vice-versa
		switch (coord)
		{
			case 'N':
			{
				room_ptr->north = temp_room_ptr;
				temp_room_ptr->south = room_ptr;
				break;
			}
			case 'S':
			{
				room_ptr->south = temp_room_ptr;
				temp_room_ptr->north = room_ptr;
				break;
			}
			case 'E':
			{
				room_ptr->east = temp_room_ptr;
				temp_room_ptr->west = room_ptr;
				break;
			}
			case 'W':
			{
				room_ptr->west = temp_room_ptr;
				temp_room_ptr->east = room_ptr;
				break;
			}
			default:
				cout << "There was an error setting pointers for the room at location: " << temp_room_ptr << endl;
		}
				
		// generate next rooms EXCEPT for the room that would be in the direction we just came from
		for(int j=0; j<4; j++)
		{
			if(rand() % selection_seed == 0)
				if(coord != coordinate_opposite[j])			// this prevents backtracking when creating more rooms
					roomGen(temp_room_ptr, selection_seed++, coordinate[j]);
		}
	}
	
	return initial_ptr				// this will give the user access to the first room, and therefore the entire complex
}

// a function will have to be written so that we can figure out what the "outermost" rooms are (leaves), then we start deleting them one at a time with 'delete' (moving up the branch) until we get to the initial room (root)