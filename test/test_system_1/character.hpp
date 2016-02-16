// character.hpp

#ifndef CHARACTER_HPP_INCLUDED     // if roomDelete.hpp hasn't been included yet...
#define CHARACTER_HPP_INCLUDED     // #define this so the compiler knows it has been included

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class character
{
public:
    character();
    void act(char input);
} ;

#endif  // CHARACTER_HPP_INCLUDED
