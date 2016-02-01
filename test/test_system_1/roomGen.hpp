// roomGen.hpp

#ifndef ROOMGEN_HPP_INCLUDED    // if roomGen.hpp hasn't been included yet...
#define ROOMGEN_HPP_INCLUDED    // #define this so the compiler knows it has been included

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

#define NUM_DOORS 4

struct coord {
    int xcoord;
    int ycoord;
} ;

struct room {
	struct room * north;
	struct room * south;
	struct room * east;
	struct room * west;

	struct coord position;
} ;

extern char compass[NUM_DOORS];
extern char compass_opposite[NUM_DOORS];

room * roomGen(room *, int, char);
room * gen_init_room(int);
void gen_room(room *, int, char);
void set_direction(room *, char, room *);
bool probability(int);

#endif  // ROOMGEN_HPP_INCLUDED
