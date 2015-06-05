// ECE 264 - Final Project
// Repository.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Master.h"
using namespace std;

const int maxSize = 10;

Repository::Repository()            //Default constructor for Repository
{
     vector <Item> tempRepositoryTemp(1, Item());
	 tempRepository = tempRepositoryTemp;
}

Repository::Repository(int repSize)
{
	vector <Item> tempRepositoryTemp(repSize, Item());
	tempRepository = tempRepositoryTemp;
}

int Repository::getRepSize()
{
	int count;
    count = tempRepository.size();
	return count;
}

void Repository::leaveItem(int repSlotNum)
{
	tempRepository.erase(tempRepository.begin()+repSlotNum);
	if (tempRepository.size() == 0)
		tempRepository.push_back(Item(0));
}

void Repository::viewInventory()
{
	cout << setfill('.') << setw(19) << left << "." << setw(29) << "Inventory" << endl;
	for (int i=1; i<=tempRepository.size(); i++)
	{
		cout << "[" << right << setw(2) << setfill(' ') << i << "] -> "
			 << setfill(' ') << setw(22) << tempRepository[i-1].getItemName()
			 << " - " << "Item Damage: " << right << setfill(' ') << setw(2) << tempRepository[i-1].getItemDamage() << endl;
	}
	cout << left << setfill('.') << setw(48) << "." << endl;
	cout << "\n";
}

void Repository::promptInventory()
{
	addItemTrue = 0;
	cout << "(To inspect an item, type \"ins\" + the inventory slot number, separated by a space):\n"
		 << "(To return to the previous option screen, type \"ret\")" << endl;
	cout << "Enter a command: ";
	cin >> functString;
	if (functString != "ret")
		cin >> slotNum;
	cout << "\n";
}

void Repository::invPromptInput()
{
	addItemTrue = 0;	// Initializes the variable that determines whether an item is added to the player's inventory to "false"
	if (functString == "use" || functString == "Use")	// If the user wants to "use" an item, then the Character's current damage is set to...
    {													// ...that of the item that they desire to use
		if ((slotNum-1)>=tempRepository.size() || slotNum<=0)	// If the user types in an inventory slot # that doesn't exist
		{
			cout << "You have entered an inventory slot position that doesn't exist, please try again..." << endl;
			cout << "\n";
			invInputCont = 0;
		}
		else
		{
			backpackSetCharDmgVar = (tempRepository[slotNum-1].getItemDamage());
			tempRepository.erase(tempRepository.begin()+(slotNum-1));
			if (tempRepository.size() ==0)
				tempRepository.insert(tempRepository.begin(), Item());
			invInputCont = 1;
		}
	}
	else if (functString == "ins" || functString == "Ins")	// If the user wants to "inspect" an item, then the Item Description of that...
	{														// ...specific item is printed out (*)...
		if ((slotNum-1)>=tempRepository.size() || slotNum<=0)	// If the user types in an inventory slot # that doesn't exist
		{
			cout << "You have entered an inventory slot position that doesn't exist, please try again..." << endl;
			cout << "\n";
			invInputCont = 0;
		}
		else	// If the user properly types in "ins" + a real slot number, then print out the description of the item in that slot
		{
			if (tempRepository[slotNum-1].itemNum !=0)	// Checks to see if the item being looked at is an "Empty"
				cout << "Item Name: " << tempRepository[slotNum-1].getItemName() << endl;	// If not, print out the item name
			cout << tempRepository[slotNum-1].getItemDes() << endl;	// ...(*) and then the program will loop back to printing out the Player's inventory
			cout << "\n";
			invInputCont = 0;
		}
	}
	else if (functString == "drp" || functString == "Drp")	// If the user wants to drop an item from their inventory
	{
		if ((slotNum-1)>=tempRepository.size() || slotNum<=0)	// If the user types in an inventory slot # that doesn't exist
		{
			cout << "You have entered an inventory slot position that doesn't exist, please try again..." << endl;
			cout << "\n";
			invInputCont = 0;
		}
		else
		{
			if (tempRepository[slotNum-1].itemNum == 0)
			{
				
				cout << "You have nothing to drop..." << endl;
				cout << "\n";
			}
			else
			{
				cout << "You have chosen to drop your " << tempRepository[slotNum-1].getItemName() << "..." << endl;
				cout << "\n";
			}
			if (tempRepository.size() == 1)
				tempRepository[0] = Item(0);
			else
				tempRepository.erase(tempRepository.begin()+(slotNum-1));
			invInputCont = 0;
		}
	}
	else if ((functString == "add") || (functString == "Add"))	// If the user would like to add an item from the desk to their inventory
	{
		if ((slotNum-1)>=tempRepository.size() || slotNum<=0)	// If the user types in an inventory slot # that doesn't exist
		{
			cout << "You have entered an inventory slot position that doesn't exist, please try again..." << endl;
			cout << "\n";
			invInputCont = 0;
		}
		/*
		else if (tempRepository.size() == 10)
		{
			repositorySwapCheck = 1;
			addItemTrue = 0;
			invInputCont = 0;
		}
		*/
		else
		{
			invInputCont = 0;
			addItemTrue = 1;
		}
	}
	else if ((functString == "ret") || (functString == "Ret"))	// If the user wants to return to the previous option screen
		invInputCont = 1;
	else	// If the user types in anything besides the listed commands, an error message is printe dout
	{
		cout << "You have entered an incorrect function, please try again:" << endl;
		cout << "\n";
		invInputCont = 0;
	}
}

Item Repository::getItem(int bpackSlot)
{
	return tempRepository[bpackSlot];
}

void Repository::addItem(Item itemToAdd)
{
	if(tempRepository[0].getItemName()=="Empty")
	{
		tempRepository.erase(tempRepository.begin());
		tempRepository.push_back(itemToAdd);
	}
	else
		tempRepository.push_back(itemToAdd);
}

Repository Repository::addItem(Repository Backpack1)	// Adds an item from a desk to the Player's backpack
{
	if (tempRepository[slotNum-1].itemNum != 0)	// If the item that the Player wants to add is not an "Empty" item...
	{
		Backpack1.addItem(tempRepository[slotNum-1]);	// ...add it normally...
		tempRepository.erase(tempRepository.begin()+(slotNum-1));	// ...and the same item from the desk, so that it can't be added more than once
		if (tempRepository.size() == 0)			// If the item taken from the desk is the last item in the desk...
			tempRepository.push_back(Item(0));	// ...add an "Empty" item to the desk
		cout << "Your current Backpack items: " << endl;
		Backpack1.viewInventory();	// Show that the item from the desk has been added to the Player's inventory
	}
	else	// Conversely, if the Player is trying to add an "Empty" item, do not perform the add, and print out a...
	{		// ...corresponding message (we can get rid of the "silly" if we need to... haha)
		cout << "There's nothing in the desk to add, silly!" << endl;
		cout << "\n";
		cout << "Your current Backpack items: " << endl;
		Backpack1.viewInventory();	// Print out the items in the Player's inventory again, just for good measure
	}
	return Backpack1;	// Return the updates that you have made to the Player's Backpack so that Player.Backpack can be reassigned...
}						// ...to Backpack1 in the Main file

void Repository::insertItem(int posToBePlaced, Item itemToBeAdded)
{
	tempRepository.insert(tempRepository.begin()+posToBePlaced, itemToBeAdded);
}

void Repository::swapPrompt()
{
	swapItemTrue = 0;
	swapPromptCont = 1;
	string tempSwapOptionString;
	cout << "You may only carry 10 items...\n"
		 << "Would you like to swap out an item in your inventory with one in the desk?\n"
		 << "[Y] = Yes\n"
		 << "[N] = No\n"
		 << "Swap? : ";
	cin >> tempSwapOptionString;
	char tempSwapOption = tempSwapOptionString[0];
	switch (tempSwapOption)
	{
	case 'y':
	case 'Y':
		cout << "Choose an inventory slot to swap the desk item with: ";
		cin >> invSlotNum;
		cout << "\n";
		swapItemTrue = 1;
		break;
	case 'n':
	case 'N':
		swapItemTrue = 0;
		break;
	default:
		cout << "You have pressed an incorrect key" << endl;
		cout << "\n";
		swapPromptCont = 0;
		break;
	}
}

Repository Repository::swapItems(Repository Backpack1)
{
	Item tempItem1;
	tempItem1 = tempRepository[slotNum-1];
	tempRepository.erase(tempRepository.begin()+(slotNum-1));
	tempRepository.push_back(Backpack1.getItem(invSlotNum-1));
	Backpack1.insertItem((invSlotNum-1), tempItem1);
	Backpack1.leaveItem((invSlotNum-1)+1);
	invInputCont = 0;
	return Backpack1;
}

void Repository::thiefChance()
{
	thiefCheckTrue = 0;
	thiefChancePerc = (rand()%100+1);
	if ((1 <= thiefChancePerc) && (thiefChancePerc <=10))	// Check to see whether or not an item should be stolen by the thief
	{
		int maxSlotNum = tempRepository.size(); 
		int itemSlotToSteal = (rand()%maxSlotNum+1);	// Randomly generate an inventory slot number to steal from
		if (tempRepository[0].itemNum !=0)									// If the Player's inventory isn't already empty...(1)
		{
			Item tempItem2 = tempRepository[itemSlotToSteal-1];								// Copy the item to steal to a temporary Item...(2)
			tempRepository.erase(tempRepository.begin()+(itemSlotToSteal-1));// (1)...steal the item from the randomly generated slot #
			cout << "Oh no!! A thief has stolen one of your items!\n"
				 << "Your " << tempItem2.getItemName() << " has been stolen..." << endl;	// (2)...so that its name can be read
			if (tempRepository.size() == 0)	// If the item stolen was the Player's only item...
				tempRepository.push_back(Item(0));		// ...add the "Empty" item to their inventory
			thiefCheckTrue = 1;
		}
	}
}