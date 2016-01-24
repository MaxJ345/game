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
bool probability(int);

int main(void)
{
	srand(time(NULL));
	room * starting_room_ptr = roomGen(NULL, 1, 'E');
}

// this code will also be eventually changed so as to work with classes (get functions, set functions, etc.)

// Need a better way of simulating "probability" of room generation. The seed and random/mod seems to have undesirable results (somewhat fixed).

/*
roomGen:
This function is called upon to recursively generate rooms. It will generate rooms to the North, South, East, and West of the current room.
The inputs are the pointer for the current room (should be NULL initially), a seed for random generation , and a direction for reference (not used for the initial function call).
The value returned by this function will be a pointer to the first room created. This should give the user access to the entire complex.
NOTE: The current version of the code does not take into account that rooms are generated without regard for each other's locations; if a 2-D grid/map was drawn of the complex, there might (and probably will) be rooms that are overlapping (take up the same spot). This doesn't break the code (these rooms will always have unique spaces allocated in memory), but it makes it confusing for the user. A way around this would be to implement a grid system that checks the location of a room before it is allocated/created.
NOTE: A value of 0 for the initial seed will cause errors.
*/

room * roomGen(room * room_ptr, int selection_seed, char direction)
{
	room * initial_ptr;

	if(room_ptr == NULL)			// base case
		initial_ptr = gen_init_room(selection_seed);			// generate initial room

	else							// recursion; note that recursion is stopped by the fact that the probability of creating a new room gets smaller as
		gen_room(room_ptr, selection_seed, direction);			// generate room

	return initial_ptr;				// this will give the user access to the first room, and therefore the entire complex
}

// function for generating the initial room
room * gen_init_room(int selection_seed)
{
	char compass[NUM_DOORS] = {'N', 'S', 'E', 'W'};

	room * initial_ptr = new room;
    cout << "Created room at location: " << initial_ptr << endl;	// for DEBUGGING

	// set all ptr's to NULL for initialization
	initial_ptr->north = NULL;
	initial_ptr->south = NULL;
	initial_ptr->east = NULL;
	initial_ptr->west = NULL;

	// this sets which "doors will be opened" (which rooms will be created) using a seed initialized by the user
	for(int i = 0; i < NUM_DOORS; i++)
	{
		if(probability(selection_seed))
			roomGen(initial_ptr, selection_seed + 1, compass[i]);
	}

	return initial_ptr;
}

// function that generates a room
void gen_room(room * room_ptr, int selection_seed, char direction)
{
	char compass[NUM_DOORS] = {'N', 'S', 'E', 'W'};
	char compass_opposite[NUM_DOORS] = {'S', 'N', 'W', 'E'};

	room * temp_room_ptr = new room;
	cout << "Created room at location: " << temp_room_ptr << endl;	// for DEBUGGING

	// set all ptr's to NULL for initialization
	temp_room_ptr->north = NULL;
	temp_room_ptr->south = NULL;
	temp_room_ptr->east = NULL;
	temp_room_ptr->west = NULL;

	// set correct direction for pointer from original room to new room, and vice-versa
	set_direction(room_ptr, direction, temp_room_ptr);

	// generate next rooms EXCEPT for the room that would be in the direction we just came from
	for(int j = 0; j < NUM_DOORS; j++)
	{
		if(probability(selection_seed))
			if(direction != compass_opposite[j])			// this prevents backtracking when creating more rooms
				roomGen(temp_room_ptr, selection_seed + 1, compass[j]);
	}
}

// function for setting the direction of ptr's between the current room and the previous room
void set_direction(room * room_ptr, char direction, room * temp_room_ptr)
{
	switch (direction)
	{
		case 'N':
			room_ptr->north = temp_room_ptr;
			temp_room_ptr->south = room_ptr;
			break;
		case 'S':
			room_ptr->south = temp_room_ptr;
			temp_room_ptr->north = room_ptr;
			break;
		case 'E':
			room_ptr->east = temp_room_ptr;
			temp_room_ptr->west = room_ptr;
			break;
		case 'W':
			room_ptr->west = temp_room_ptr;
			temp_room_ptr->east = room_ptr;
			break;
		default:
			cout << "There was an error setting pointers for the room at location: " << temp_room_ptr << endl;
	}
}

// function that returns either 'true' or 'false' based on some internal-probabilistic logic
bool probability(int seed)
{
	bool prob_out = false;

	if(rand() % seed == 0)
		prob_out = true;

	return prob_out;
}
