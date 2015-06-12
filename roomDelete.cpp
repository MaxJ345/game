#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

#define NUM_DOORS 4

struct room {
	int number;				// simulating content
	struct room * north;
	struct room * south;
	struct room * east;
	struct room * west;
} ;

roomDelete(room *, char);

int main(void)
{
	return 0;
}

/*
roomDelete:
This function deletes a complex of interlinked 'rooms'.
The function takes an initial pointer (to a room) and coordinate (should be NULL for initial value) as input.
The function returns a value based on the success/failure of the function.
*/

int roomDelete(room * room_ptr, char coord)
{
	char coordinate[NUM_DOORS] = {'N', 'S', 'E', 'W'};
	char coordinate_opposite[NUM_DOORS] = {'S', 'N', 'W', 'E'};
	char coord_opp = '\0';
	
	if(coord == '\0')	// this is the beginning/initial room
	{
		for(int i = 0; i < NUM_DOORS; i++)
		{
			switch (coordinate[i])
			{
				case 'N':
				{
					if(room_ptr->north != NULL)
						roomDelete(room_ptr->north, 'N');
					break;
				}
				case 'S':
				{
					if(room_ptr->south != NULL)
						roomDelete(room_ptr->south, 'S');
					break;
				}
				case 'E':
				{
					if(room_ptr->east != NULL)
						roomDelete(room_ptr->east, 'E');
					break;
				}
				case 'W':
				{
					if(room_ptr->west != NULL)
						roomDelete(room_ptr->west, 'W');
					break;
				}
				default:
					cout << "There was an error deallocating for the room at location: " << room_ptr << endl;
			}
		}
		
		if(room_ptr->north == NULL && room_ptr->south == NULL && room_ptr->east == NULL && room_ptr->west == NULL)
			delete room_ptr;
		else
			return 2;		// outward rooms have not been deleted yet
	}		
	
	else		// recursion
	{
		// this sets the value for the door that won't be handed to the delete function
		for(int j = 0; j < NUM_DOORS; j++)
		{
			if(coord == coordinate[j])
				coord_opp = coordinate_opposite[j];
		}
		
		if(coord_opp == '\0')
		{
			cout << "An error occurred while setting the value of the opposite coordinate.\n"
			return 1;
		}
		
		for(int k = 0; k < NUM_DOORS; k++)
		{
			if(coordinate[k] != coord_opp)		// this is to avoid backtracking (which would probably cause infinite recursion)
			{
				switch (coordinate[k])
				{
					case 'N':
					{
						if(room_ptr->north != NULL)
							roomDelete(room_ptr->north, 'N')
						break;
					}
					case 'S':
					{
						if(room_ptr->south != NULL)
							roomDelete(room_ptr->south, 'S')
						break;
					}
					case 'E':
					{
						if(room_ptr->east != NULL)
							roomDelete(room_ptr->east, 'E')
						break;
					}
					case 'W':
					{
						if(room_ptr->west != NULL)
							roomDelete(room_ptr->west, 'W')
						break;
					}
					default:
						cout << "There was an error deallocating for the room at location: " << room_ptr << endl;
				}
			}
		}
		
		// delete connection (ptr's) between current room and previous
		switch(coord)
		{
			case 'N':
			{
				room_ptr->south->north = NULL;
				room_ptr->south = NULL;
			}
			case 'S':
			{
				room_ptr->north->south = NULL;
				room_ptr->north = NULL;
			}
			case 'E':
			{
				room_ptr->west->east = NULL;
				room_ptr->west = NULL;
			}
			case 'W':
			{
				room_ptr->east->west = NULL;
				room_ptr->east = NULL;
			}
			default:
				cout << "There was a problem with severing the connection for the room at location: " << room_ptr << endl;
		}
		
		if(room_ptr->north == NULL && room_ptr->south == NULL && room_ptr->east == NULL && room_ptr->west == NULL)
			delete room_ptr;
		else
			return 3;		// outward rooms have not been deleted yet
	}
	
	return 0;	// successful in deallocating the entire complex
}