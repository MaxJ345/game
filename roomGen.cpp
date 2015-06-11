#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct room {
	int number;				// simulating content
	struct room * north;
	struct room * south;
	struct room * east;
	struct room * west;
} ;

room * roomGen(room *, int, char);

int main(void)
{
	srand(time(NULL));
	room * starting_room_ptr = roomGen(NULL, 1, 'E');
}

// A function will have to be written so that we can figure out what the "outermost" rooms are (leaves), then we start deleting them one at a time with 'delete' (moving up the branch) until we get to the initial room (root); this will all be needed for deallocation.

// this code will also be eventually changed so as to work with classes (get functions, set functions, etc.)

// Need a better way of simulating "probability" of room generation. The seed and random/mod seems to have undesirable results (somewhat fixed).

/*
roomGen:
This function is called upon to recursively generate rooms. It will generate rooms to the North, South, East, and West of the current room.
The inputs are the pointer for the current room (should be NULL initially), a seed for random generation , and a coordinate for reference (not used for the initial value).
The value returned by this function will be a pointer to the first room created. This should give the user access to the entire complex.
NOTE: The current version of the code does not take into account that rooms are generated without regard for each other's locations; if a 2-D grid/map was drawn of the complex, there might (and probably will) be rooms that are overlapping (take up the same spot). This doesn't break the code (these rooms will always have unique spaces allocated in memory), but it makes it confusing for the user. A way around this would be to implement a grid system that checks the location of a room before it is allocated/created.
NOTE: A value of 0 for the initial seed will cause errors.
*/

room * roomGen(room * room_ptr, int selection_seed, char coord)
{
	char coordinate[4] = {'N', 'S', 'E', 'W'};
	char coordinate_opposite[4] = {'S', 'N', 'W', 'E'};
	room * initial_ptr;
	int temp_seed;

	if(room_ptr == NULL)			// base case
	{
		initial_ptr = new room;
		
		// this sets which "doors will be opened" (which rooms will be created) using a seed initialized by the user
		for(int i=0; i<4; i++)
		{
		    temp_seed = selection_seed;
			if(rand() % selection_seed == 0)
				roomGen(initial_ptr, ++temp_seed, coordinate[i]);			// selection_seed needs to be pre-incremented, otherwise the incremented value never makes it into the "deeper levels" of recursion
		}
	}

	else							// recursion; note that recursion is stopped by the fact that the probability of creating a new room gets smaller as recursion gets deeper
	{
		room * temp_room_ptr = new room;
		
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
		    temp_seed = selection_seed;
			if(rand() % selection_seed == 0)
				if(coord != coordinate_opposite[j])			// this prevents backtracking when creating more rooms
					roomGen(temp_room_ptr, ++temp_seed, coordinate[j]);
		}
	}

	return initial_ptr;				// this will give the user access to the first room, and therefore the entire complex
}
