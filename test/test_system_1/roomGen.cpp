//roomGen.cpp

#include "roomGen.hpp"

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
	room * initial_ptr = new room;
    //cout << "Created room at location: " << initial_ptr << endl;	// for DEBUGGING

	// set all ptr's to NULL for initialization
	initial_ptr->north = NULL;
	initial_ptr->south = NULL;
	initial_ptr->east = NULL;
	initial_ptr->west = NULL;

	// set the coordinates
	initial_ptr->position.xcoord = 0;
	initial_ptr->position.ycoord = 0;

	coord temp_position;
	temp_position.xcoord = initial_ptr->position.xcoord;
	temp_position.ycoord = initial_ptr->position.ycoord;

	pCoordList->push_front(temp_position);

	//cout << initial_ptr->position.xcoord << ", " << initial_ptr->position.ycoord << endl;	// for DEBUGGING

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
	room * temp_room_ptr = new room;
    //cout << "Created room at location: " << temp_room_ptr << endl;	// for DEBUGGING

	// set all ptr's to NULL for initialization
	temp_room_ptr->north = NULL;
	temp_room_ptr->south = NULL;
	temp_room_ptr->east = NULL;
	temp_room_ptr->west = NULL;

	// initialize the coordinates
	temp_room_ptr->position.xcoord = room_ptr->position.xcoord;
	temp_room_ptr->position.ycoord = room_ptr->position.ycoord;

	// Set the coordinates.
	set_coordinates(direction, temp_room_ptr);

	// Checking to see if the current room's position is already occupied. If it is, delete this current room, otherwise continue.
	coord temp_position;
	temp_position.xcoord = temp_room_ptr->position.xcoord;
	temp_position.ycoord = temp_room_ptr->position.ycoord;
	if(inList(temp_position))
    {
        delete temp_room_ptr;
    }
    else
    {
        // Add the current room's coordinates to the list, so we can keep track of its position.
        pCoordList->push_front(temp_position);

        // set correct direction for pointer from original room to new room, and vice-versa
        set_direction(room_ptr, direction, temp_room_ptr);

        //cout << temp_room_ptr->position.xcoord << ", " << temp_room_ptr->position.ycoord << endl;  // for DEBUGGING

        // generate next rooms EXCEPT for the room that would be in the direction we just came from
        for(int j = 0; j < NUM_DOORS; j++)
        {
            if(probability(selection_seed))
                if(direction != compass_opposite[j])			// this prevents backtracking when creating more rooms
                    roomGen(temp_room_ptr, selection_seed + 1, compass[j]);
        }
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

// function to set the coordinates of the current room
void set_coordinates(char direction, room * temp_room_ptr)
{
    switch (direction)
    {
        case 'N':
            (temp_room_ptr->position.ycoord)++;
            break;
        case 'S':
            (temp_room_ptr->position.ycoord)--;
            break;
        case 'E':
            (temp_room_ptr->position.xcoord)++;
            break;
        case 'W':
            (temp_room_ptr->position.xcoord)--;
            break;
        default:
            cout << "There was an error setting the coordinates for the room at location: " << temp_room_ptr << endl;
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

bool inList(coord pos)
{
    bool inList = false;
    list <coord>::iterator coord_iterator = pCoordList->begin();

    for(; coord_iterator != pCoordList->end(); coord_iterator++)
    {
        coord temp = *coord_iterator;
        if(pos.xcoord == temp.xcoord && pos.ycoord == temp.ycoord)
        {
            inList = true;
            //cout << "room already exists at: " << pos.xcoord << ", " << pos.ycoord << endl; // for DEBUGGING
            break;
        }
    }

    return inList;
}
