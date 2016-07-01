// main.cpp

#include "roomGen.hpp"
#include "roomDelete.hpp"
#include "character.hpp"
#include "prompt.hpp"

#include "stash.hpp"

int main(void)
{
	srand(time(NULL));
	room * starting_room_ptr = roomGen(NULL, 1, '\0');

    character * player = new character();
    player->set_location(starting_room_ptr);

    prompt * interface = new prompt(player);
    interface->sort_list();
    interface->find_extremes();
    interface->drawMap();

stash test;

test.add_items();

cout << test.get_item_list(true, true, true);

item * item_test = test.get_item(2,false);
cout << item_test->get_itemName() << endl;

item * new_item;
new_item = new item;
new_item->set_itemName("test");
test.add_item(new_item);

item_test = test.get_item(3,true);
cout << item_test->get_itemName() << endl;

//item_test = test.get_item(3,false);     // should fail due to there being no item in this location
cout << item_test->get_itemName() << endl;


    bool bAskUserInput = true;
    while(bAskUserInput)
    {
        bAskUserInput = interface->request();
    }

    roomDelete(starting_room_ptr, '\0');
}
