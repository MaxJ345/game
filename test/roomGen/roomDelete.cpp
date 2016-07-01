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

int roomDelete(room *, char);
void seek(room *, char);
void sever_connections(room * room_ptr, char direction);

int main(void)
{
	return 0;
}

/*
roomDelete:
This function deletes a complex of interlinked 'rooms'.
The function takes an initial pointer (to a room) and direction (should be NULL for initial value) as input.
The function returns a value based on the success/failure of the function.
*/

int roomDelete(room * room_ptr, char direction)
{
	char compass[NUM_DOORS] = {'N', 'S', 'E', 'W'};
	char compass_opposite[NUM_DOORS] = {'S', 'N', 'W', 'E'};
	char direction_opp = '\0';
	
	// base case
	if(direction == '\0')	// this is the beginning/initial room
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
			if(direction == compass[j])
				direction_opp = compass_opposite[j];
		}
		
		if(direction_opp == '\0')
		{
			cout << "An error occurred while setting the value of the opposite direction.\n";
			return 1;
		}
		
		// call function on any remaining rooms
		seek(room_ptr, direction_opp);
		
		// delete connection (ptr's) between current room and previous
		sever_connections(room_ptr, direction);
		
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
void seek(room * room_ptr, char direction_opp)
{
	char compass[NUM_DOORS] = {'N', 'S', 'E', 'W'};
	
	for(int i = 0; i < NUM_DOORS; i++)
	{
		if(compass[i] != direction_opp)		// this is to avoid backtracking (which would cause infinite recursion)
		{
			switch (compass[i])
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
void sever_connections(room * room_ptr, char direction)
{
	switch(direction)
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
