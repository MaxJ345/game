// main.cpp

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdio.h>

using namespace std;

#include "roomGen.hpp"
#include "roomDelete.hpp"
#include "character.hpp"

int main(void)
{
	srand(time(NULL));
	room * starting_room_ptr = roomGen(NULL, 1, '\0');

	//roomDelete(starting_room_ptr, '\0');

    character player1;
    player1.act('L');

    room * temp_room_ptr = starting_room_ptr;

    // for DEBUGGING
    cout << temp_room_ptr->position.xcoord << ", " << temp_room_ptr->position.ycoord << endl;

    char userInput = '\0';
    while(userInput != 'Q')
    {
        // Read user input.
        cin >> userInput;
        //cin.get(userInput);
        //cin.clear();
        //userInput = getchar();
        //cout << "\n";

        // Act based on user input.
        switch(userInput)
        {
            case 'n':
            case 'N':
                if(temp_room_ptr->north != NULL)
                    temp_room_ptr = temp_room_ptr->north;
                break;
            case 's':
            case 'S':
                if(temp_room_ptr->south != NULL)
                    temp_room_ptr = temp_room_ptr->south;
                break;
            case 'e':
            case 'E':
                if(temp_room_ptr->east != NULL)
                    temp_room_ptr = temp_room_ptr->east;
                break;
            case 'w':
            case 'W':
                if(temp_room_ptr->west != NULL)
                    temp_room_ptr = temp_room_ptr->west;
                break;
            default:
                break;
        }

        // for DEBUGGING
        if(userInput != '\n' && userInput != 'Q')
            cout << temp_room_ptr->position.xcoord << ", " << temp_room_ptr->position.ycoord << endl;
    }
}
