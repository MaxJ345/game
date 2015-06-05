
roomGen(* room_ptr, int selection_seed, char coord)
{
	//bool whichRoom[4]={True, True, True, True};	// not needed?
	char coordinate[4]={'N', 'S', 'E', 'W'};
	char coordinate_opposite[4]={'S', 'N', 'W', 'E'};
	srand(time(NULL));
	
	if(room_ptr == NULL)			// base case
	{
		initial_ptr = malloc(room);
		
		// this sets which "doors will be opened" (which rooms will be created) using a seed initialized by the user
		for(int i=0; i<4; i++)
		{
			if(rand() % selection_seed == 0)
				roomGen(initial_ptr, selection_seed++, coordinate[i]);
		}
	}
	else							// recursion; note that recursion is stopped by the fact that the probability of creating a new room gets smaller as recursion gets deeper
	{
		temp_room_ptr = malloc(room);
		
		room_ptr->coord = temp_room_ptr;
		temp_room_ptr->coordinate_opposite = room_ptr;
		
		// next rooms
	}
	
	return initial_ptr				// this will give the user access to the first room, and therefore the entire complex
}