// ECE 264 - Final Project
// Character.cpp

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Master.h"
using namespace std;

Character::Character()	// Default constructor for Character
{
	setCharacterHealth(100);	// Initializes Character Health to 100
	setCharacterDamage(0);		// Initializes Character Damage to 0
}

Character::Character(int rooms[], string roomNames[], int nRooms, string roomDes[], string roomWin[])
{
	setCharacterHealth(100);	// Initializes Character Health to 100
	setCharacterDamage(0);		// Initializes Character Damage to 0
	location = 0;
	pNRooms=nRooms;

	for(int i=0; i<nRooms; i++)
	{
			pRooms[i] = rooms[i];
			pRoomNames[i] = roomNames[i];
			pRoomDes[i] = roomDes[i];
			pRoomWin[i] = roomWin[i];
	}
}

int Character::prompt()
{
	char userInput;
	char letterString[27]={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	// check the current character location

	cout << "Your current options are:\n" << endl;
	cout<<"["<<"Q"<<"]"<<" View Inventory."<<endl;

	if(location==0)
	{
		for(int i=1; i<=pNRooms; i++)
		{
			cout<< "[" << letterString[i-1] << "]" << " Enter The " << pRoomNames[i-1] << " Room." << endl;
		}
		cout << "[" << "Z" << "]" << " Fight The Boss!" << endl;
		cout << "Enter a command: ";
	}
	else
	{
		// print room description
		// room options
		// interact with room and desk (repository)
		cout << "[" << "R" << "]" << " Return to the hallway." << endl;
		cout << "[" << "W" << "]" << " Inspect the window." << endl;
		cout << "[" << "Y" << "]" << " Inspect the desk." << endl;
		cout << "Enter a command: ";
	}

	cin >> userInput;
	cout << "\n";

	if(location==0)
	{
		switch(userInput)
		{
		case 'a':
		case 'A':
			location=1;
			cout << "You are now in The " << pRoomNames[location-1] << " Room.\n" << pRoomDes[location-1] << '\n' << endl;
			return 1;
			//break;
		case 'b':
		case 'B':
			location=2;
			cout << "You are now in The " << pRoomNames[location-1] << " Room.\n" << pRoomDes[location-1] << '\n' << endl;
			return 2;
			//break;
		case 'c':
		case 'C':
			location=3;
			cout << "You are now in The " << pRoomNames[location-1] << " Room.\n" << pRoomDes[location-1] << '\n' << endl;
			return 3;
			//break;
		case 'd':
		case 'D':
			location=4;
			cout << "You are now in The " << pRoomNames[location-1] << " Room.\n" << pRoomDes[location-1] << '\n' << endl;
			return 4;
			//break;
		case 'e':
		case 'E':
			location=5;
			cout << "You are now in The " << pRoomNames[location-1] << " Room.\n" << pRoomDes[location-1] << '\n' << endl;
			return 5;
			//break;
		case 'f':
		case 'F':
			location=6;
			cout << "You are now in The " << pRoomNames[location-1] << " Room.\n" << pRoomDes[location-1] << '\n' << endl;
			return 6;
			//break;
		case 'g':
		case 'G':
			location=7;
			cout << "You are now in The " << pRoomNames[location-1] << " Room.\n" << pRoomDes[location-1] << '\n' << endl;
			return 7;
			//break;
		case 'h':
		case 'H':
			location=8;
			cout << "You are now in The " << pRoomNames[location-1] << " Room.\n" << pRoomDes[location-1] << '\n' << endl;
			return 8;
			//break;
		case 'i':
		case 'I':
			location=9;
			cout << "You are now in The " << pRoomNames[location-1] << " Room.\n" << pRoomDes[location-1] << '\n' << endl;
			return 9;
			//break;
		case 'j':
		case 'J':
			location=10;
			cout << "You are now in The " << pRoomNames[location-1] << " Room.\n" << pRoomDes[location-1] << '\n' << endl;
			return 10;
			//break;
		case 'k':
		case 'K':
			location=11;
			cout << "You are now in The " << pRoomNames[location-1] << " Room.\n" << pRoomDes[location-1] << '\n' << endl;
			return 11;
			//break;
		case 'l':
		case 'L':
			location=12;
			cout << "You are now in The " << pRoomNames[location-1] << " Room.\n" << pRoomDes[location-1] << '\n' << endl;
			return 12;
			//break;
		case 'm':
		case 'M':
			location=13;
			cout << "You are now in The " << pRoomNames[location-1] << " Room.\n" << pRoomDes[location-1] << '\n' << endl;
			return 13;
			//break;
		case 'n':
		case 'N':
			location=14;
			cout << "You are now in The " << pRoomNames[location-1] << " Room.\n" << pRoomDes[location-1] << '\n' << endl;
			return 14;
			//break;
		case 'o':
		case 'O':
			location=15;
			cout << "You are now in The " << pRoomNames[location-1] << " Room.\n" << pRoomDes[location-1] << '\n' << endl;
			return 15;
			//break;
		case 'q':
		case 'Q':
			return 69;	// open inventory
			//break;
		case 'z':
		case 'Z':
			{
			string tempBossSelectionString;
			char tempBossSelection;
			cout << "You have selected to enter the boss room...\n"
				 << "It is advised that you try and fill up your backpack with items before continuing!\n"
				 << "Would you like to continue?\n"
				 << "(Enter either 'Yes' or 'No'): ";
			cin >> tempBossSelectionString;
			tempBossSelection = tempBossSelectionString[0];
			switch (tempBossSelection)
			{
			case 'y':
			case 'Y':
				cout << "\nMay the force be with you, brave one...\n\n";
				location = 300;
				return 66;
				// Breaks the loop and continue onto boss fight (based on the check in the main);
			case 'n':
			case 'N':
				cout << "\n";
				return 0;
				// Restarts the prompt loop
			default:
				cout << "That is not a valid input. Please try again" << endl;
				cout << "\n";
				return 0;
				// Restarts the prompt loop
			}
			}
		default:
			cout<<"That is not a valid input. Please try again.\n"<<endl;
			return 0;
		}
	}
	else
	{
		switch(userInput)
		{
		case 'q':
		case 'Q':
			// open inventory
			return 69;
			//break;
		case 'r':
		case 'R':
			location=0;
			cout << "You are now in the hallway." << endl;
			return 0;
			//break;
		case 'w':
		case 'W':
			cout<<pRoomWin[location-1]<<'\n'<<endl;
			break;
		case 'y':
		case 'Y':
			// return a value? that leads to desk print/prompt/etc..???
			// inspect desk
			// print out desk
			return 96;
		default:
			cout<<"That is not a valid input.\n"<<"Try doing that from the hallway.\n"<<endl;
			return 101;
		}
	}
}

void Character::charDetermineDamage()
{
	int critChance, missChance; // Variables used for setting up the chances that the Player either misses or successfully performs a critical hit 	
	charCheckCrit = false;	// Initialize the Player's critical hit chance to false
	charCheckMiss = false;	// Initialize the Player's miss chance to false
	critChance = (rand()%100+1); // Generates a random # used later in determining if the Player performed a critical hit
	missChance = (rand()%100+1); // Generates a random # used later in determining if the Player missed in their attack
	if ((1<=critChance)&&(critChance<=10))	// Creates a window of 10 out of 100 possible numbers, corresponding to a 10% chance of a...
	{										// ...Player critical hit
		charCheckCrit = true;
	}
	if ((1<=missChance)&&(missChance<=10))	// Creates a window of 10 out of 100 possible numbers, corresponding to a 10% chance of a...
	{										// ...Player attack miss
		charCheckMiss = true;
	}
	charDamage = (rand()%5+1);	// Generates a random # between 1 and 5 corresponding to the amount of damage that the Player does
	if (charCheckCrit && charCheckMiss) // If the Critical Hit and Miss chances both return true
	{
		int decideCritOrMiss;	// Introduce a new integer that randomly decides whether the attack is a "Critical Hit" or "Miss"
		decideCritOrMiss = (rand()%2+1); // Randomly generate a number between 1 and 2 to determine the Player Attack outcome
		if (decideCritOrMiss == 1)		 // If randomly generated # is 1...
			charCheckCrit = true;			 // ...the Player attack is treated as a Critical Hit
		else							 // If randomly generated # is 2...
			charCheckMiss = true;			 // ...the Player attack is treated as a Miss
	}									 
	else if (charCheckCrit)						 // If a Player critical hit is successful...
	{								      
		charDamage = 1.5*charDamage;	 // ...the new Player damage = (1.5 * [the # between 1 and 10 that was previously generated for charDamage]).
	}						
	else if (charCheckMiss)						 // If the Player's attack misses the boss during combat...
	{									  
		charDamage = 0;					 // ...then the Player does 0 damage.
	}
}

void Character::charCombatPrompt()
{
	string tempCombatOptionString;
	cout << "Combat Options:" << endl;
	cout << "[F] : Fight! (using fists)\n"
		 << "[I] : Check Items" << endl;
	cout << "Please enter a command: ";
	cin >> tempCombatOptionString;
	cout << "\n";
	tempCombatOption = tempCombatOptionString[0];
}

void Character::charCombatInput()
{
	switch (tempCombatOption)
	{
	case 'f':
	case 'F':
		charDetermineDamage();
		combInputCont = 1;
		break;
	case 'i':
	case 'I':
		combInputCont = 0;
		break;
	default:
		cout << "You have pressed an incorrect key" << endl;
		cout << "\n";
		combInputCont = 0;
		break;
	}
}

void Character::charCombatScript()
{
	switch (tempCombatOption)
	{	
	case 'f':
	case 'F':
		// Check to see what the normal fight combat script should be based on whether the Player missed or critically hit
		if ((getCheckCrit()==false)&&(getCheckMiss()==false))	// If the attack does a normal amount of damage
			cout << "Player deals a physical attack for " << getCharacterDamage() << " damage" << endl;
		else if (getCheckCrit()==true)	// If the Player's attack is a critical hit
		{
			cout << "Player deals a physical attack for " << getCharacterDamage() << " damage\n";
			cout << "(Player's attack is a critical hit!)" << endl;
		}
		else if (getCheckMiss()==true)	// If the Player's attack has missed
			cout << "Player's attack has missed causing " << getCharacterDamage() << " damage" << endl;
		cout << "\n";
		break;
	case 'i':
	case 'I':
		cout << "Player uses the selected item for " << getCharacterDamage() << " damage" << endl;
		cout << "\n";
		break;
	default:
		break;
	}
}

void Character::setCharacterHealth(float health)
{
	charHealth = health;
}

float Character::getCharacterHealth()
{
	return charHealth;
}

void Character::setCharacterDamage(float dmg)
{
	charDamage = dmg;
}

float Character::getCharacterDamage()
{
	return charDamage;
}

bool Character::getCheckCrit()
{
	return charCheckCrit;
}

bool Character::getCheckMiss()
{
	return charCheckMiss;
}