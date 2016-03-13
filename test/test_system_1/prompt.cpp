// prompt.cpp

#include "prompt.hpp"

prompt::prompt(character * playerPtr)
{
    if(playerPtr != NULL)
        player = playerPtr;
    else
        cout << "Initial character position is NULL!";
}

bool prompt::request()
{
    bool retValue = true;
    room * temp_room_ptr = player->get_location();

    // for DEBUGGING
    cout << temp_room_ptr->position.xcoord << ", " << temp_room_ptr->position.ycoord << endl;

    string strUserInput;

    getline(cin, strUserInput);

    switch(strUserInput[0])
    {
        case 'n':
        case 'N':
            if(temp_room_ptr->north != NULL)
                player->set_location(temp_room_ptr->north);
            break;
        case 's':
        case 'S':
            if(temp_room_ptr->south != NULL)
                player->set_location(temp_room_ptr->south);
            break;
        case 'e':
        case 'E':
            if(temp_room_ptr->east != NULL)
                player->set_location(temp_room_ptr->east);
            break;
        case 'w':
        case 'W':
            if(temp_room_ptr->west != NULL)
                player->set_location(temp_room_ptr->west);
            break;
        case 'm':
        case 'M':
            drawMap();
            break;
        default:
            retValue = false;
            break;
    }

    return retValue;
}

// This function sorts the coord list based on a custom compare function (specifically made for the coord struct).
void prompt::sort_list()
{
    pCoordList->sort(compare_origin_top_left);
}

// This function will find the 'edges' (top, left, bottom, right) of the map.
void prompt::find_extremes()
{
    list <coord>::iterator coord_iterator = pCoordList->begin();

    for(; coord_iterator != pCoordList->end(); coord_iterator++)
    {
        coord coord_temp = *coord_iterator;

        // for DEBUGGING
        //cout << coord_temp.xcoord << ", " << coord_temp.ycoord << endl;

        if(coord_temp.ycoord > upperMost)       // Acquire the highest ycoord.
            upperMost = coord_temp.ycoord;

        if(coord_temp.xcoord < leftMost)        // Acquire the lowest xcoord.
            leftMost = coord_temp.xcoord;

        if(coord_temp.ycoord < downMost)        // Acquire the lowest ycoord.
            downMost = coord_temp.ycoord;

        if(coord_temp.xcoord > rightMost)       // Acquire the highest xcoord.
            rightMost = coord_temp.xcoord;
    }

    // for DEBUGGING
    //cout << "upper-most: " << upperMost << endl;
    //cout << "left-most: " << leftMost << endl;
    //cout << "down-most: " << downMost << endl;
    //cout << "right-most: " << rightMost << endl;
}

// This function draws the map, based on the coord list.
void prompt::drawMap()
{
    for(int ixY = upperMost; ixY >= downMost; ixY--)
    {
        for(int line = 1; line <= 5; line++)       // This loop is needed for printing multiple lines for each row on the map.
        {

            for(int ixX = leftMost; ixX <= rightMost; ixX++)
            {
                coord temp_coord;
                temp_coord.xcoord = ixX;
                temp_coord.ycoord = ixY;

                // Binary search will return true if a matching coord is in the list. This determines whether we draw the room or a blank space on the map.
                if(binary_search(pCoordList->begin(), pCoordList->end(), temp_coord, compare_origin_top_left))
                    printRoom(line, temp_coord);
                else
                    printBlank();
            }
            cout << endl;

        }
    }
}

// This function prints a simple outline of a room. It will also mark the room if it is the player's current location.
void prompt::printRoom(int line, coord current_coord)
{
    if(line == 1 || line == 5)
        cout << "`````";
    else if(line == 2 || line == 4)
    {
        cout << "`   `";
    }
    else
    {
        coord player_coord = player->get_location()->position;
        if(player_coord.xcoord == current_coord.xcoord && player_coord.ycoord == current_coord.ycoord)
            cout << "` * `";
        else
            cout << "`   `";
    }
}

// This function simply prints blanks for empty spaces.
void prompt::printBlank()
{
    cout << "     ";
}

// This function needs to be used as a reference for comparison in the list::sort() and algorithm::binary_search() functions. This function is used to determine the "sorting" of the coord structure.
bool prompt::compare_origin_top_left(const coord & lhs, const coord & rhs)
{
    if(lhs.ycoord == rhs.ycoord)                // If at the same ycoord...
        return (lhs.xcoord < rhs.xcoord);       // Sort by xcoord (from left to right).
    else                                        // Else...
        return (lhs.ycoord > rhs.ycoord);       // Sort by ycoord (from up to down).
}
