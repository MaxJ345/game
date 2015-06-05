// ECE 264 - Final Project
// Item.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Master.h"
using namespace std;
#define const int maxItemSize = 20;

Item::Item()
{
    itemName = "Empty";
	itemNum = 0;
	itemDamage = 0;
	itemDes = "What's to explain? There's nothing there...";
}

Item::Item(int num)
{
	itemNum = num;
	switch (itemNum)
        // weight is damage points
        // type: 1 = room item; 0 = backpack item
   {
    case 0:
		itemName = "Empty";
        itemDamage=0;
		itemDes = "What's to explain? There's nothing there...";
        break;

    case 1:    
		itemName = "Clock";
		itemDamage = 1;
		itemDetermineDamage();
		itemDes = "This old analog clock may not be good for telling time anymore but it sure is heavy...";
        break;

    case 2:    
		itemName = "Candle Stick Holder";
        itemDamage=1;
		itemDetermineDamage();
		itemDes = "This item is pretty much useless... try throwing it at someone.";
        break;

    case 3:   
		itemName = "Ax";
        itemDamage=6;
		itemDetermineDamage();
		itemDes = "It may be old and rusty, but that only makes it more dangerous!\nThis is one of the most powerful items in the game!";
        break;

    case 4:    
		itemName = "Key";
        itemDamage=1;
		itemDetermineDamage();
		itemDes = "All the doors are already unlocked, but this key seems to be...\n...especially sharp making it an excellent eye poker outer.";
        break;

    case 5:    
		itemName = "Hammer";
        itemDamage=4;
		itemDetermineDamage();
		itemDes = "This massive hammer is extremely heavy and can surely cause a lot of damage.";
        break;

    case 6:    
		itemName = "Katana";
        itemDamage=8;
		itemDetermineDamage();
		itemDes = "This powerful blade was once used by an ancient Japanese daimyo of legend.";
        break;

    case 7:    
		itemName = "Pool Stick";
        itemDamage=5;
		itemDetermineDamage();
		itemDes = "You've already seen what it can do to a cue ball... Try using it on the boss!";
        break;

    case 8:    
		itemName = "Flash Light";
        itemDamage=2;
		itemDetermineDamage();
		itemDes = "The batteries are dead but this item still may be useful...";
        break;

    case 9:    
		itemName = "Iron Pipe";
        itemDamage=4;
		itemDetermineDamage();
		itemDes = "This pipe is made of pure iron and is incredibly heavy making it perfect to throw at an enemy.";
        break;

    case 10:    
		itemName = "Machete";
        itemDamage=9;
		itemDetermineDamage();
		itemDes = "This machete has a very large blade capable of causing heavy damage.";
        break;

    case 11:    
		itemName = "Frozen Leg Of Lamb";
        itemDamage=3;
		itemDetermineDamage();
		itemDes = "We're not quite sure where it came from... but it's as good of a blunt object as anything.";
        break;

    case 12:    
		itemName = "Monkey Wrench";
        itemDamage=6;
		itemDetermineDamage();
		itemDes = "Forget about the Foo Fighters song! Let's try swinging this as something.";
        break;

    case 13:    
		itemName = "Smoke Bomb";
        itemDamage=3;
		itemDetermineDamage();
		itemDes = "It's rumored the boss has bad asthma... Try throwing this near him.";
        break;

    case 14:    
		itemName = "Balloon";
        itemDamage=0;
		itemDes = "Maybe the boss will laugh himself to death when he sees you try to use this...";
        break;

    case 15:    
		itemName = "Pistol";
        itemDamage=13;
		itemDetermineDamage();
		itemDes = "A nice 9mm will deter most enemies...";
        break;

    case 16:    
		itemName = "Nail Board";
        itemDamage=10;
		itemDetermineDamage();
		itemDes = "A wooden 2 by 4 with a nail hammered through one end.\nFavored weapon of the super mutants from Fallout.";
        break;

    case 17:
		itemName = "Wiffle Ball Bat";
        itemDamage=2;
		itemDetermineDamage();
		itemDes = "This plastic bat is very light but its long reach may be useful";
        break;

    case 18:    
		itemName = "Louisville Slugger";
        itemDamage=8;
		itemDetermineDamage();
		itemDes = "This heavy wooden baseball bat is capable of knocking someone out cold!";
        break;

    case 19:    
		itemName = "Chain Saw";
        itemDamage=10;
		itemDetermineDamage();
		itemDes = "This chain saw still has a little bit of gas in it...\nIt's just waiting to be used to cut someone in half.";
        break;

	default:
		itemName = "Empty";
		itemDamage = 0;
		itemDes = "What's to explain? There's nothing there...";
		break;
	}
}

void Item::itemDetermineDamage()
{
	itemDamage = itemDamage + (rand()%3);	// Randomize itemDamage up to a max of itemDamage + 3
}

string Item::getItemDes()
{
	return itemDes;
}

void Item::setItemName(string name)
{
	itemName = name;
}

string Item::getItemName()
{
	return itemName;
}

void Item::setItemDamage(int weight)
{
	itemDamage = weight;
}

int Item::getItemDamage()
{
	return itemDamage;
}