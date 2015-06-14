#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

#define NUM_DOORS 4

struct room {
	struct room * north;
	struct room * south;
	struct room * east;
	struct room * west;
} ;

room * roomGen(room *, int, char);
room * gen_init_room(int);
void gen_room(room *, int, char);
void set_direction(room *, char, room *);

int roomDelete(room *, char);
void seek(room *, char);
void sever_connections(room * room_ptr, char coord);

int main(void)
{
	srand(time(NULL));
	room * starting_room_ptr = roomGen(NULL, 1, 'E');

	int test = roomDelete(starting_room_ptr, '\0');
	cout << test << endl;
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
	room * initial_ptr;

	if(room_ptr == NULL)			// base case
		initial_ptr = gen_init_room(selection_seed);	// generate initial room

	else							// recursion; note that recursion is stopped by the fact that the probability of creating a new room gets smaller as
		gen_room(room_ptr, selection_seed, coord);			// generate room

	return initial_ptr;				// this will give the user access to the first room, and therefore the entire complex
}

// function for generating the initial room
room * gen_init_room(int selection_seed)
{
	int temp_seed;
	char coordinate[NUM_DOORS] = {'N', 'S', 'E', 'W'};

	room * initial_ptr = new room;
    cout << "Created room at location: " << initial_ptr << endl;

	//set all ptr's to NULL for initialization
	initial_ptr->north = NULL;
	initial_ptr->south = NULL;
	initial_ptr->east = NULL;
	initial_ptr->west = NULL;

	// this sets which "doors will be opened" (which rooms will be created) using a seed initialized by the user
	for(int i = 0; i < NUM_DOORS; i++)
	{
		temp_seed = selection_seed;
		if(rand() % selection_seed == 0)
			roomGen(initial_ptr, ++temp_seed, coordinate[i]);			// selection_seed needs to be pre-incremented, otherwise the incremented value never makes it into the "deeper levels" of recursion
	}

	return initial_ptr;
}

// function that generates a room
void gen_room(room * room_ptr, int selection_seed, char coord)
{
	int temp_seed;
	char coordinate[NUM_DOORS] = {'N', 'S', 'E', 'W'};
	char coordinate_opposite[NUM_DOORS] = {'S', 'N', 'W', 'E'};

	room * temp_room_ptr = new room;
	cout << "Created room at location: " << temp_room_ptr << endl;

	//set all ptr's to NULL for initialization
	temp_room_ptr->north = NULL;
	temp_room_ptr->south = NULL;
	temp_room_ptr->east = NULL;
	temp_room_ptr->west = NULL;

	// set correct direction for pointer from original room to new room, and vice-versa
	set_direction(room_ptr, coord, temp_room_ptr);

	// generate next rooms EXCEPT for the room that would be in the direction we just came from
	for(int j = 0; j < NUM_DOORS; j++)
	{
		temp_seed = selection_seed;
		if(rand() % selection_seed == 0)
			if(coord != coordinate_opposite[j])			// this prevents backtracking when creating more rooms
				roomGen(temp_room_ptr, ++temp_seed, coordinate[j]);
	}
}

// function for setting the direction of ptr's between the current room and the previous room
void set_direction(room * room_ptr, char coord, room * temp_room_ptr)
{
	char coordinate[NUM_DOORS] = {'N', 'S', 'E', 'W'};

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
}

int roomDelete(room * room_ptr, char coord)
{
	char coordinate[NUM_DOORS] = {'N', 'S', 'E', 'W'};
	char coordinate_opposite[NUM_DOORS] = {'S', 'N', 'W', 'E'};
	char coord_opp = '\0';

	// base case
	if(coord == '\0')	// this is the beginning/initial room
	{
		// call the function on any remaining rooms
		seek(room_ptr, '\0');

		// delete current room
		if(room_ptr->north == NULL && room_ptr->south == NULL && room_ptr->east == NULL && room_ptr->west == NULL)
		{
			cout << "Deleting room at location: " << room_ptr << endl;
			delete room_ptr;
		}
		else
			return 2;		// outward rooms have not been deleted yet
	}

	// recursion
	else
	{
		// this sets the value for the door that won't be handed to the delete function
		for(int j = 0; j < NUM_DOORS; j++)
		{
			if(coord == coordinate[j])
				coord_opp = coordinate_opposite[j];
		}

		if(coord_opp == '\0')
		{
			cout << "An error occurred while setting the value of the opposite coordinate.\n";
			return 1;
		}

		// call function on any remaining rooms
		seek(room_ptr, coord_opp);

		// delete connection (ptr's) between current room and previous
		sever_connections(room_ptr, coord);

		// delete current room
		if(room_ptr->north == NULL && room_ptr->south == NULL && room_ptr->east == NULL && room_ptr->west == NULL)
		{
			cout << "Deleting room at location: " << room_ptr << endl;
			delete room_ptr;
		}
		else
			return 3;		// outward rooms have not been deleted yet
	}

	return 0;	// successful in deallocating the entire complex
}

// function for seeking which rooms to further delete
void seek(room * room_ptr, char coord_opp)
{
	char coordinate[NUM_DOORS] = {'N', 'S', 'E', 'W'};

	for(int i = 0; i < NUM_DOORS; i++)
	{
		if(coordinate[i] != coord_opp)		// this is to avoid backtracking (which would cause infinite recursion)
		{
			switch (coordinate[i])
			{
				case 'N':
					if(room_ptr->north != NULL)
						roomDelete(room_ptr->north, 'N');
					break;
				case 'S':
					if(room_ptr->south != NULL)
						roomDelete(room_ptr->south, 'S');
					break;
				case 'E':
					if(room_ptr->east != NULL)
						roomDelete(room_ptr->east, 'E');
					break;
				case 'W':
					if(room_ptr->west != NULL)
						roomDelete(room_ptr->west, 'W');
					break;
				default:
					cout << "There was an error deallocating for the room at location: " << room_ptr << endl;
			}
		}
	}
}

// function that severs the connections between the current room and the previous room
void sever_connections(room * room_ptr, char coord)
{
	switch(coord)
	{
		case 'N':
			room_ptr->south->north = NULL;
			room_ptr->south = NULL;
			break;
		case 'S':
			room_ptr->north->south = NULL;
			room_ptr->north = NULL;
			break;
		case 'E':
			room_ptr->west->east = NULL;
			room_ptr->west = NULL;
			break;
		case 'W':
			room_ptr->east->west = NULL;
			room_ptr->east = NULL;
			break;
		default:
			cout << "There was a problem with severing the connection for the room at location: " << room_ptr << endl;
	}
}
