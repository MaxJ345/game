// prompt.cpp

#include "prompt.hpp"

prompt::prompt(room * charPos)
{
    if(charPos != NULL)
        character_position = charPos;
    else
        cout << "Initial character position is NULL!";
}

int prompt::request()
{
    string strUserInput;
    int retVal = 0;

    getline(cin, strUserInput);

    switch(strUserInput[0])
    {
        case 'n':
        case 'N':
            retVal = 50;
            break;
        case 's':
        case 'S':
            retVal = 51;
            break;
        case 'e':
        case 'E':
            retVal = 52;
            break;
        case 'w':
        case 'W':
            retVal = 53;
            break;
        default:
            break;
    }

    return retVal;
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
        for(int ixX = leftMost; ixX <= rightMost; ixX++)
        {
            coord temp_coord;
            temp_coord.xcoord = ixX;
            temp_coord.ycoord = ixY;

            // Binary search will return true if a matching coord is in the list. This determines whether we draw the room or a blank space on the map.
            if(binary_search(pCoordList->begin(), pCoordList->end(), temp_coord, compare_origin_top_left))
                cout << "*";
            else
                cout << "-";
        }
        cout << endl;
    }
}

// This function needs to be used as a reference for comparison in the list::sort() and algorithm::binary_search() functions. This function is used to determine the "sorting" of the coord structure.
bool prompt::compare_origin_top_left(const coord & lhs, const coord & rhs)
{
    if(lhs.ycoord == rhs.ycoord)                // If at the same ycoord...
        return (lhs.xcoord < rhs.xcoord);       // Sort by xcoord (from left to right).
    else                                        // Else...
        return (lhs.ycoord > rhs.ycoord);       // Sort by ycoord (from up to down).
}
