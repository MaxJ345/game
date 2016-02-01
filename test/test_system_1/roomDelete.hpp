// roomDelete.hpp

#ifndef ROOMDELETE_HPP_INCLUDED     // if roomDelete.hpp hasn't been included yet...
#define ROOMDELETE_HPP_INCLUDED     // #define this so the compiler knows it has been included

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "roomGen.hpp"

int roomDelete(room *, char);
void seek(room *, char);
void sever_connections(room * room_ptr, char direction);

#endif  // ROOMDELETE_HPP_INCLUDED
