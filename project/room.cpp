// room.cpp

#include "room.hpp"

char compass[NUM_DOORS] = {'N', 'S', 'E', 'W'};
char compass_opposite[NUM_DOORS] = {'S', 'N', 'W', 'E'};

list <coord> * pCoordList = new list <coord>;
int upperMost = 0;
int leftMost = 0;
int downMost = 0;
int rightMost = 0;
