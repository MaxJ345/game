// list::empty
#include <iostream>
#include <list>
using namespace std;

struct room {
    int content;
	struct room * north;
	struct room * south;
	struct room * east;
	struct room * west;
} ;

int main ()
{
    list<room *> mylist;

//    cout << ( mylist.empty() ? "List is empty.\n" : "List is not empty.\n" ) << endl;

//  ORIGINAL -----------------------------

    room * room1 = new room;
    room1->content = 15;

    cout
    << room1->content << "\n";

    cout << room1 << "\n" << endl;

    mylist.push_front(room1);

//    cout << ( mylist.empty() ? "List is empty.\n" : "List is not empty.\n" ) << endl;

//    delete room1;                             // This line would cause some of the remaining addresses to be wrong.

//  TEST -----------------------------

    room test_room = *(mylist.front());

    cout
    << test_room.content << "\n";

    cout << &test_room << "\n" << endl;

//  ITERATOR -----------------------------

    std::list<room *>::iterator test_room_ptr = mylist.begin();

    cout
    << (*test_room_ptr)->content << "\n";

    cout
    << (*test_room_ptr) << "\n";                // This value is the same as the one below, because 'content' is the first piece of the 'room' structure.

    cout
    << &(*test_room_ptr)->content << "\n";

    cout
    << &(*test_room_ptr) << "\n"  << endl;

//  LIST -----------------------------

    cout
    << mylist.front()->content << "\n";

    cout << mylist.front() << "\n" << endl;

    return 0;
}
