// ECE 264 - Final Project
// Driver program for class Boss

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Master.h"
using namespace std;

int main()
{
// ********************************************************************
// *******************         INITIALIZATIONS      *******************
// ********************************************************************
	srand(time(NULL));	// Initialize random seed
	Room roomArray;		// Initializes stuff for the array of all rooms that will be used...
	Boss Boss1;			// Creates the game's Boss
	int promptCheck = 0;	// Variable used in checking the Player's input to the room prompts
	
	// Constructor that gives the Player access to basically all of the randomly generated information from roomArray
	Character Player(roomArray.roomLottery, roomArray.roomNames, roomArray.nRooms, roomArray.roomDescriptions, roomArray.roomWindow);
	Player.Backpack.addItem(Item(0));	// Makes sure that the Player starts with an "Empty" inventory

	vector <Repository> arrayOfDesks(roomArray.nRooms, Repository());	// Creates a vector of desks to be used throughout the game. The amount
	for (int i=0; i<arrayOfDesks.size(); i++)							// ...of desks created is the same as the amount of rooms
	{
		int amtOfItems = (rand()%2+1);	// Initializes a random # from 1-2 for the amount of items generated in any given desk
		for (int j=1; j<=amtOfItems; j++)
		{
			int randItemNum = (rand()%19+1);	// Initializes a random # from 1-19 for the actual items that are going...		
			Item tempItem1 = Item(randItemNum);	// ...to be initialized in each desk
			arrayOfDesks[i].addItem(tempItem1);
		}
	}

/*
// Code to print out all of the randomly generated desks (for debugging purposes)
	cout << arrayOfDesks.size() << " desks have been created" << endl;
	for (int i=0; i<arrayOfDesks.size(); i++)
	{
		cout << "Desk " << i << ":\n";
		arrayOfDesks[i].viewInventory();
	}
*/
// Code used to manually add items to the Player's inventory at the start of the game (for debugging purposes)
	Item empty(0), clock(1), csh(2), ax(3), key(4), hammer(5), katana(6), pool_stick(7), flashlight(8), iron_pipe(9);
	Item machete (10), flol(11), m_w(12), sm_bmb(13), balloon(14), pistol(15), nail_b(16), wbb(17), louie_s(18), ch_saw(19);
	Player.Backpack.addItem(machete);
	Player.Backpack.addItem(csh);
	Player.Backpack.addItem(key);
	Player.Backpack.addItem(katana);
	Player.Backpack.addItem(pool_stick);
	Player.Backpack.addItem(flashlight);
	Player.Backpack.addItem(iron_pipe);
	Player.Backpack.addItem(louie_s);
	Player.Backpack.addItem(wbb);
	Player.Backpack.addItem(pistol);

// ********************************************************************
// *********************      ROOM PHASE      *************************
// ********************************************************************

	while(promptCheck!=66)
	{
		promptCheck=Player.prompt();	// Prompt the player to decide on a room to go into
//		------------------------
//		|  Check Thief Phase   |
//		------------------------
		if ((1 <= promptCheck) && (promptCheck <=15))	// If the player has just selected to go into a room
        {
            Player.Backpack.thiefChance();	// Check to see if the thief has stolen an item, and assign the update to the Player's Backpack if so
			if (Player.Backpack.thiefCheckTrue == 1)	// If the thief has stolen an item...
				Player.Backpack.viewInventory();		// ...show the Player's inventory for convenience's sake
        }																	
//		-------------------------
//		|   Inventory Options   |
//		-------------------------
		if (promptCheck ==69)	// View inventory / maybe perform some inventory functions
		{
			do
			{
				Player.Backpack.viewInventory();
				cout << "(To drop an item type \"drp\" + the inventory slot number of the item to drop):" << endl;
				Player.Backpack.promptInventory();
				Player.Backpack.invPromptInput();
			} while (Player.Backpack.invInputCont ==0);
		}
//		-------------------------
//		|     Desk Options      |
//		-------------------------
		else if (promptCheck ==96)	// View desk items / Swap item from desk to inventory / Add item from desk to inventory
		{
			do
			{
				cout << "Contents of the desk in The " << Player.pRoomNames[Player.location-1] << " Room: " << endl; // Heading for desk items
				arrayOfDesks[Player.location-1].viewInventory();	// Show the desk items of the room that the Player is currently in
				cout << "(To add an item type \"add\" + the Desk slot number of the item to add):" << endl;
				arrayOfDesks[Player.location-1].promptInventory();
				arrayOfDesks[Player.location-1].invPromptInput();
				if ((Player.Backpack.getRepSize() == 10) && ((arrayOfDesks[Player.location-1].functString == "add") || 
					(arrayOfDesks[Player.location-1].functString == "Add")))	// If Backpack == "full" & the player wants to add an item
				{
					cout << "Your current Backpack items: " << endl;
					Player.Backpack.viewInventory();	// Show the Player's inventory
					do
					{
						arrayOfDesks[Player.location-1].swapPrompt();	// Ask the player if they would like to swap an item
					} while(arrayOfDesks[Player.location-1].swapPromptCont == 0); // If the player does not successfully type in a yes or a no...
																				  // ...repeat the prompt
					if (arrayOfDesks[Player.location-1].swapItemTrue == 1)	// If the Player has decided to swap an item...
						Player.Backpack = arrayOfDesks[Player.location-1].swapItems(Player.Backpack);	// ...then swap and update the backpack
				}
				else // If the Player's Backpack is not full, simply add the item from the desk to the end of the Backpack...
				{	 // ...(and also delete the desk item so that the player can't add the same item more than once) 
					arrayOfDesks[Player.location-1].invPromptInput();
					if (arrayOfDesks[Player.location-1].addItemTrue == 1)	// If the Player decides to add an item...
						Player.Backpack = arrayOfDesks[Player.location-1].addItem(Player.Backpack);	// ...add the item and update Player.Backpack
				}
			} while (arrayOfDesks[Player.location-1].invInputCont ==0);
		}
	}

// ********************************************************************
// ****************   BOSS vs. PLAYER COMBAT PHASE   ******************
// ********************************************************************
	do 
	{
//		-------------------------
//		| Print out Health Bars |
//		-------------------------
		Boss1.printHealthBars(Boss1, Player);

//		-------------------------
//		| Player Attack Phase	|
//		-------------------------
		Player.charCombatPrompt();	// Initially prompt the Player for their choice of combat option (i.e. F = fight, I = view items)
		Player.charCombatInput();	// Initially take the Player's input from the previous prompt
		while (Player.combInputCont ==0)	// Check the Player's input to the previous prompt - This check will return a 0, if the Player...
		{									// ...has not yet finished their combat phase, thereby continuing the loop. Conversely, this check...
			do								// ...will return a 1 if the Player has chosen an option for their combat phase (ending the loop).														
			{
				Player.Backpack.viewInventory();	// Show Player inventory
				if (Player.location == 300)
					cout << "(To use an item, type \"use\" + the inventory slot number, separated by a space):" << endl;
				Player.Backpack.promptInventory();	// Give the Player a prompt to choose an option
				Player.Backpack.invPromptInput();
				if (Player.Backpack.functString == "use")
				{
					Player.combInputCont = 1;
					Player.setCharacterDamage(Player.Backpack.backpackSetCharDmgVar);
				}
			} while (Player.Backpack.invInputCont ==0);	// Get the Player's option
			if (Player.Backpack.functString != "use")
			{
				Player.charCombatPrompt();
				Player.charCombatInput();
			}
		}// If there is an error, or if the user inspects an item, loop back and do everything over again
		
		Player.charCombatScript();		// Print out the script for the Player's attack

		Boss1.setBossHealth(Boss1.getBossHealth()-Player.getCharacterDamage());	// bossHealth = bossHealth - characterDamage
		Boss1.printHealthBars(Boss1, Player);
		if (Boss1.getBossHealth() <= 0)											// Check to see if the Boss has been killed...
			break;																// ...If so, break out of the loop				
//		-------------------------
//		| Boss Attack Phase     |
//		-------------------------
		Boss1.bossDetermineDamage();	// Determines the damage done by the next boss attack
		Boss1.bossCombatScript();		// Determines the script based on what the Boss attack type is

		Player.setCharacterHealth(Player.getCharacterHealth()-Boss1.getBossDamage());	// characterHealth = characterHealth - bossDamage
		if (Player.getCharacterHealth() <= 0)											// Check to see if Player has been killed...
			break;																		// ...If so, break out of the loop

//		-------------------------
//		| Is Combat Phase Done? |
//		-------------------------
	// Loop combat phase until either Boss or Player dies
	} while ((Player.getCharacterHealth() > 0) && (Boss1.getBossHealth() > 0));

//		-------------------------
//		| Game Over Messages	|
//		-------------------------
	if (Player.getCharacterHealth() <= 0)
	{
		cout << "Game Over. You Lose! It sucks to suck...\n\n";
	}
	else
	{
		cout << "You've beaten the Boss! Congratulations! You win the game!\n\n";
	}
	return 0;
}