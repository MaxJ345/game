// character.hpp

#ifndef CHARACTER_HPP_INCLUDED     // if character.hpp hasn't been included yet...
#define CHARACTER_HPP_INCLUDED     // #define this so the compiler knows it has been included

#include "room.hpp"

class character
{
public:
    character();
    void act(char input);
    room * get_location();
    void set_location(room * input_room_ptr);

private:
    room * location;
} ;

#endif  // CHARACTER_HPP_INCLUDED
