// character.cpp

#include "character.hpp"

character::character()
{
    location = new room;
}

void character::act(char input)
{

}

room * character::get_location()
{
    return location;
}

void character::set_location(room * input_room_ptr)
{
    location = input_room_ptr;
}
