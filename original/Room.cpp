// ECE 264 - Final Project
// Room.cpp

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Master.h"
using namespace std;

Room::Room()
{
	string roomNamesTemplate[20] = {"Laboratory","Class","Dining","Large",
		"Orange","Fire","Lavender","Smoking","Leisure","Sun","Living",
		"Bath","Black","Candy","Odorous","Art","Egyptian","Dungeon",
		"Game","Sloth Master Bed"};
	
	string roomDescriptionTemplate[20] = {"You see an assortment of test tubes, beakers, and other experimental instruments.\nYou feel a large, hairless, mutant creature scurry across your feet\nas it runs to the other side of the room. The smell of chemicals\nfills the air making it difficult to breathe.",
		"You see an old chalk board at the front of the room that reads 'Get out while you can!'.\nYou see a human skeleton on a stand in the corner from an anatomy class.\nAn sense of eeriness comes over you.",
		"Spoons, forks, knives, plates, and old scraps of food litter the floor.\nThe pungent aroma of rotten food fills the air.",
		"This room is very spacious, it has high ceilings and a lot of floor space.\nYou feel that this rooms holds a certain emptiness like something is missing from it.",
		"As you enter this room you are immediately able to see that the walls,\nand all items in it are orange. Additionally, the room smells like oranges\nwhich seems odd because you are unable to find any traces of said fruit.",
		"All items in the room are black and chared and the room smells like a camp fire.\nIt is immediately apparent that the room has been burned.",
		"As you enter the room you smell the faint scent of lavender.\nYou see lavender plants scattered throughout the room\nand notice that they seem to be growing out of the concrete floor somehow.",
		"The smell of cigar smoke is saturated into this room.\nTobacco litters the floor and makes a crunching sound everytime you step on it.\nDrew sits in the corner rolling a cigarette. But where is his jug of water!?",
		"You see many large chairs and couches in this room.\nA soothing aroma fills your nose and you feel relaxed.",
		"This room is made completely out of glass and is very bright.\nYou immediately feel warm upon entering the room.",
		"Upon entering, you see two couches and a coffee table that face an entertainment system.\nAn old children's television show is playing on the broken TV screen\nbut you are unable to identify what it is. You feel at home and comfortable\nbut at the same time slightly uneasy, like something awful happened here.",
		"White porcelain covers the room. Although you see a toilet, sink and trash can,\nthe room smells clean like somebody cleaned it before it was abandoned.",
		"This room is pitch black. The walls are painted black making it impossible to see anyting.\nYou think you hear something scratching at the walls but you can't tell what it is.",
		"As you step into this room you feel a sticky substance under your feet.\nYou see candy wrappers on the floor and chocolate on the walls.\nYou realize how hungry you are and look for any uneaten candy but find none.",
		"There are few physical features to this room, however there is an awful smell,\na mixture of dead animal and rotten eggs. The smell is so bad\nthat your eyes start to water making it difficult to see.",
		"The walls are covered with various paintings; you recognize a Picasso, a Van Gough,\nand a Rembrant. You realize that all of these paintings had been stolen\nfrom various museums and are worth millions of dollars. You contemplate\nstealing them from the room but decide that carrying around large paintings\nwould be very counterproductive in helping you escape.",
		"As you enter you see a silhouette of a sarcophagous standing in the back of the room.\nHieroglyphics paint the large brick walls.\nYou see countless ancient treasures of gold, diamonds, and rubies.",
		"You see a bed of spikes covered in blood. You see wrist straps hanging from the ceiling\nand a tub of dirty water in the middle of the room.",
		"As you enter you bump into a billiards table. You notice a dart board on the wall and a\npoker table on the far side of the room. On the poker table lies a perfect royal flush.",
		"A sloth lays sloth-like on a bed of soft pillows in the Sloth Master Bedroom.\nBefore the sloth falls back asleep he mutters 'Do you like dragons?'"
	};
	
	string roomWindowTemplate[20] = {"The window has burn marks from a chemical explosion.",
		"The window has the word 'HELP' written backwards in magic marker on it.",
		"The window has a substance that resembles frosting smered by someone's hand on it.",
		"The window is the size of an entire wall of the room.\nYou feel small standing infront of it.",
		"The window is made of stained glass pannels that are orange in color.",
		"The window is completely covered in soot making it impossible to look out of.",
		"The window is clear and you can see more lavender plants\ngrowing in the window box outside.",
		"The window is covered in soot and ash which cuts off most outside light.",
		"The window is covered by a red velvet curtain.",
		"All of the windows are clear to let in an optimal amount of light.",
		"The window is covered in colorful stickers of animals\nand a small toy car was left on the window sill.",
		"There is a small window above the toilet but it is too\nhigh for you to see out of.",
		"The window has been covered with boards which blocks any light from entering.",
		"The window has been covered by bubble gum.",
		"You see a window in the corner of the room but you are unable\nto stay in the room long enough to inspect it.",
		"The window has a circular cut mark on it like somebody was trying to break\ninto the room but were unable to get through the glass.",
		"The window does not have any glass, it is just a hole\ncausing the room to be very cold.",
		"The window has 5 scratch marks on it like someone was\nscratching it with their finger nails.",
		"A blood-covered playing card is stuck to the broken pane of the window.",
		"There is no window, only a tree with thick branches that stands in the room."
	};

	nRooms=10+(rand()%(15-10+1));

	int tempRandom = 0;
	roomLottery[15] = (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
	int repeat = 1;

	for(int i=0; i<nRooms; i++)
	{
		while(repeat)
		{
			tempRandom=(rand()%(19+1));
			for(int j=0; j<nRooms; j++)
			{
				if((tempRandom+1)==roomLottery[j])
				{
					repeat=1;
					break;
				}
				else
					repeat=0;
			}
		}
		roomLottery[i]=tempRandom+1;
		roomNames[i]=roomNamesTemplate[tempRandom];
		roomDescriptions[i]=roomDescriptionTemplate[tempRandom];
		roomWindow[i]=roomWindowTemplate[tempRandom];
		repeat=1;
	}
}