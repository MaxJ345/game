// main.cpp

#include "roomGen.hpp"
#include "roomDelete.hpp"
#include "character.hpp"
#include "prompt.hpp"

void game_initiate(character *, prompt *);

int main(void)
{
	srand(time(NULL));
	room * starting_room_ptr = roomGen(NULL, 1, '\0');

	//roomDelete(starting_room_ptr, '\0');

    character * player = new character();
    player->set_location(starting_room_ptr);

    prompt * interface = new prompt(player->get_location());

    interface->sort_list();
    interface->find_extremes();
    interface->drawMap();

    //game_initiate(player, interface);
}

void game_initiate(character * player, prompt * interface)
{
    room * temp_room_ptr = player->get_location();

    // for DEBUGGING
    cout << temp_room_ptr->position.xcoord << ", " << temp_room_ptr->position.ycoord << endl;

    int promptResult = 66;
    while(promptResult != 0)
    {
        promptResult = interface->request();

        // Act based on user input.
        switch(promptResult)
        {
            case 50:
                if(temp_room_ptr->north != NULL)
                    player->set_location(temp_room_ptr->north);
                break;
            case 51:
                if(temp_room_ptr->south != NULL)
                    player->set_location(temp_room_ptr->south);
                break;
            case 52:
                if(temp_room_ptr->east != NULL)
                    player->set_location(temp_room_ptr->east);
                break;
            case 53:
                if(temp_room_ptr->west != NULL)
                    player->set_location(temp_room_ptr->west);
                break;
            default:
                break;
        }

        temp_room_ptr = player->get_location();

        // for DEBUGGING
        if(promptResult != 0)
            cout << temp_room_ptr->position.xcoord << ", " << temp_room_ptr->position.ycoord << endl;

    }

}
