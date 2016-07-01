// stash.hpp

#ifndef STASH_HPP_INCLUDED     // if stash.hpp hasn't been included yet...
#define STASH_HPP_INCLUDED     // #define this so the compiler knows it has been included

#include "includes.hpp"
#include "item.hpp"

#define MAX_NUM_ITEMS 10

class stash
{
public:
    stash();

    void add_items();
    string get_item_list(bool bShowDes, bool bShowWeight, bool bShowDamage);    // Prints list of all items in stash.
    int get_num_items();        // Retrieves number of items currently in this stash.
    item * get_item(int nIndex, bool bTakeFromStash);
    bool add_item(item * newItem);
    //drop item function
    //swap item function (returns item, takes in item and index)

    // NOTE: Make a global list of all items (off the prompt class maybe?). Get rid of the get_item_list() method above and use it instead to populate the global list of items. Then use the global list to fill stashes (backpack, rooms, etc.).

private:
    array <item *, MAX_NUM_ITEMS> * pItemList;        // A list of items.
    void process_item_info(string strLine, item * itemPtr);

    int numItems;               // Current number of items in this stash.

} ;

#endif  // STASH_HPP_INCLUDED

