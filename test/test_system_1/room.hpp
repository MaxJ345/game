// room.hpp

#ifndef ROOM_HPP_INCLUDED     // if room.hpp hasn't been included yet...
#define ROOM_HPP_INCLUDED     // #define this so the compiler knows it has been included

#include "includes.hpp"

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

extern list <coord> * pCoordList;       // A list of all the rooms (based on their coordinates).
extern int upperMost;                   // Reference of the upper-most coord.
extern int leftMost;                    // Reference of the left-most coord.
extern int downMost;                    // Reference of the down-most coord.
extern int rightMost;                   // Reference of the right-most coord.

#endif  // ROOM_HPP_INCLUDED

