// prompt.hpp

#ifndef PROMPT_HPP_INCLUDED     // if prompt.hpp hasn't been included yet...
#define PROMPT_HPP_INCLUDED     // #define this so the compiler knows it has been included

#include "character.hpp"

class prompt
{
public:
    prompt(character *);

    bool request();

    void sort_list();
    void find_extremes();
    void drawMap();

    static bool compare_origin_top_left(const coord &, const coord &);

private:
    character * player;

} ;

#endif  // PROMPT_HPP_INCLUDED
