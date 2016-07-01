// roomGen.hpp

#ifndef ROOMGEN_HPP_INCLUDED    // if roomGen.hpp hasn't been included yet...
#define ROOMGEN_HPP_INCLUDED    // #define this so the compiler knows it has been included

#include "room.hpp"

using namespace std;
room * roomGen(room *, int, char);
room * gen_init_room(int);
void gen_room(room *, int, char);
void set_coordinates(char, room *);
void set_direction(room *, char, room *);
bool probability(int);
bool inList(coord);

#endif  // ROOMGEN_HPP_INCLUDED
