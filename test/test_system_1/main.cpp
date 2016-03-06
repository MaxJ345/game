// main.cpp

#include "roomGen.hpp"
#include "roomDelete.hpp"
#include "character.hpp"
#include "prompt.hpp"

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

    bool bAskUserInput = true;
    while(bAskUserInput)
    {
        bAskUserInput = interface->request();
    }

    roomDelete(starting_room_ptr, '\0');
}
