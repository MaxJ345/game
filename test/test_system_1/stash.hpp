// stash.hpp

#ifndef STASH_HPP_INCLUDED     // if stash.hpp hasn't been included yet...
#define STASH_HPP_INCLUDED     // #define this so the compiler knows it has been included

#include "includes.hpp"
#include "item.hpp"

class stash
{
public:
    stash();

    void get_items();

private:
    list <item> * pItemList;        // A list of items.
    void process_item_info(string strLine, item * itemPtr);

} ;

#endif  // STASH_HPP_INCLUDED

