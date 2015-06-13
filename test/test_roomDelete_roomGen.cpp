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


room * roomGen(room *, int, char);
int roomDelete(room *, char);

int main(void)
{
/*	room * test_ptr = new room;
	cout << "Created room at location: " << test_ptr << endl;
	test_ptr->north = NULL;
	test_ptr->south = NULL;
	test_ptr->east = NULL;
	test_ptr->west = NULL;

	test_ptr->north = new room;
	cout << "Created room at location: " << test_ptr->north << endl;
	test_ptr->north->north = NULL;
	test_ptr->north->south = test_ptr;
	test_ptr->north->east = NULL;
	test_ptr->north->west = NULL;
*/
/*	test_ptr->north = new room;
	cout << "Created room at location: " << test_ptr->north << endl;
	test_ptr->south = new room;
	cout << "Created room at location: " << test_ptr->south << endl;
	test_ptr->east = new room;
	cout << "Created room at location: " << test_ptr->east << endl;
	test_ptr->west = new room;
	cout << "Created room at location: " << test_ptr->west << endl;
*/
    srand(time(NULL));
    room * test_ptr = roomGen(NULL, 1, '\0');

    int test = roomDelete(test_ptr, '\0');

    cout << test << endl;

	return 0;
}

room * roomGen(room * room_ptr, int selection_seed, char coord)
{
	char coordinate[NUM_DOORS] = {'N', 'S', 'E', 'W'};
	char coordinate_opposite[NUM_DOORS] = {'S', 'N', 'W', 'E'};
	room * initial_ptr;
	int temp_seed;

	if(room_ptr == NULL)			// base case
	{
		initial_ptr = new room;
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
	}

	else							// recursion; note that recursion is stopped by the fact that the probability of creating a new room gets smaller as recursion gets deeper
	{
		room * temp_room_ptr = new room;
		cout << "Created room at location: " << temp_room_ptr << endl;

		//set all ptr's to NULL for initialization
		temp_room_ptr->north = NULL;
		temp_room_ptr->south = NULL;
		temp_room_ptr->east = NULL;
		temp_room_ptr->west = NULL;

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
		for(int j = 0; j < NUM_DOORS; j++)
		{
		    temp_seed = selection_seed;
			if(rand() % selection_seed == 0)
				if(coord != coordinate_opposite[j])			// this prevents backtracking when creating more rooms
					roomGen(temp_room_ptr, ++temp_seed, coordinate[j]);
		}
	}

	return initial_ptr;				// this will give the user access to the first room, and therefore the entire complex
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
        {
            cout << "Deleting room at location: " << room_ptr << endl;
            delete room_ptr;
        }
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
			cout << "An error occurred while setting the value of the opposite coordinate.\n";
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
		}

		// delete connection (ptr's) between current room and previous
		switch(coord)
		{
			case 'N':
			{
				room_ptr->south->north = NULL;
				room_ptr->south = NULL;
				break;
			}
			case 'S':
			{
				room_ptr->north->south = NULL;
				room_ptr->north = NULL;
				break;
			}
			case 'E':
			{
				room_ptr->west->east = NULL;
				room_ptr->west = NULL;
				break;
			}
			case 'W':
			{
				room_ptr->east->west = NULL;
				room_ptr->east = NULL;
				break;
			}
			default:
				cout << "There was a problem with severing the connection for the room at location: " << room_ptr << endl;
		}

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
