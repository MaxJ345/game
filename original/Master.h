// ECE 264 - Final Project
// Master Header File (All class declerations)

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

class Item
{
public:
	Item();
	Item(int);
	int loseItem(int);
	int addItem(int, int, int);
	void itemDetermineDamage();

	string getItemDes();
	void setItemName(string);
	string getItemName();
	void setItemDamage(int);
	int getItemDamage();
	int itemNum;
private:
	string itemDes;
	string itemName;
	int itemDamage;
};

class Repository
{
public:
     Repository();	// Default constructor
	 Repository(int);
     int getRepSize();
	 int repositorySwapCheck;	// Variable used within the main loop in determining when a swap should be made
	 void leaveItem(int);
	 void viewInventory();
	 void promptInventory();
	 void invPromptInput();
	 void addItem(Item);	// Used when simply passing an item to a repository to add
	 Repository addItem(Repository);	// Used when the item to add is coming from another repository
	 void insertItem(int, Item);	// Function used to add an item to a specific slot number in a repository
	 void swapPrompt();	// Prints out that the Player has 10 items in their inventory, and takes in the desk / backpack slots to switch between
	 Repository swapItems(Repository);	// The code that actually swaps the items between a desk and the backpack
	 Item getItem(int);	// Function that returns an item based on a passed Repository slot number
	 void thiefChance();	// Function that acts as a thief and randomly steals a (random) item from the Player's inventory
	 int thiefCheckTrue;	// Variable used in the main to figure out whether or not the inventory should be printed out after...
							// ...an item is stolen
	 int thiefChancePerc;
	 int invSlotNum;	// Variable that takes in a value during an item swap between Desk & Inventory
	 int addItemTrue;	// A flag used in the main in determining whether or not an item should be added to the Player's backpack
	 int swapItemTrue;	// A flag used in the main to determine whether or not an item should be swapped between Backpack & a desk
	 int swapPromptCont;	// A flag used in the swapPrompt loop to determine when the loop should be broken out of

	 int backpackSetCharDmgVar;	// Variable that returns the damage of the item that the Player selects (used in main for...
								// ...setting the Player's damage)
	 string tempString, slotNumString, functString;
	 bool invInputCont;	// Variable used in determining the flow of the check inventory loop in the main
	 int slotNum;
private:
	vector <Item> tempRepository;
};

class Character
{
public:
	Character();
	Character(int rooms[], string roomNames[], int nRooms, string roomDes[], string roomWin[]);
	int prompt();
	void charDetermineDamage();	// Function to help randomize the Player damage
	void charCombatPrompt();	// Prints out the Player's options for combat
	void charCombatInput();		// Gets the Player's inputted combat option
	void charCombatScript();	// Prints out the Player's attack and the damage that it has dealt to the Boss\

	void setCharacterHealth(float);
	float getCharacterHealth();
	void setCharacterDamage(float);
	float getCharacterDamage();

	int location;
	int pRooms[15];	// doesn't the vector 'rooms' have to have room numbers, names, description, etc.? ; or maybe use these ints to refer to other vectors with those elements
	string pRoomNames[15];
	int pNRooms;
	string pRoomDes[15];
	string pRoomWin[15];

	bool getCheckCrit();	// Returns the current value of the Critical Hit Check
	bool getCheckMiss();	// Returns the current value of the Attack Miss Check
	bool combInputCont;		// Variable used in determining the flow of the main program loop ("Combat Input Continue?")

	char tempCombatOption;	// Used in storing the user's inputted combat option
	Repository Backpack;
private:
	bool charCheckCrit;			// Variable that returns true during charDetermineDamage if the Player's attack is a critical hit
	bool charCheckMiss;			// Variable that returns true during charDetermineDamage if the Player's attack misses
	float charHealth;		// Current value of the Player's health (originally set to 100)
	float charDamage;		// The damage that the Player does to the Boss (randomly generated [1:5] when Player selects "Fight"...
							// ...and determined by the item selection when Player selects "Item")
};

class Room
{
public:
    Room();	// Default constructor

	int nRooms;
	int roomLottery[15];
	string roomNames[15];
	string roomDescriptions[15];
	string roomWindow[15];
	vector <Repository> arrayOfDesks;

	void deskRandomizeItems();
	void showAllDesks();
private:	
};

class Boss
{
public:
	Boss(); // Default constructor
	void bossDetermineDamage(); // Sets the Boss's damage value to a random # between 1 & 10 (also determines whether or not the...
								// ...Boss's attack is a "Critical Hit" or a "Miss" - 10% chance for either)
	int bossAttackType(); // Only used in determining what the combat script is for the Boss attack...
						  // ...For Ex:) 1 = "Physical Attack" ; 2 = "Fireball", etc...
	string printBossAttackType(); // Used for printing out the Boss attack type
	void bossCombatScript();	// Prints out a script for the Boss's attack
	void setBossDamage(float);  // If for whatever reason we need to set the Boss's damage to a specific value
	float getBossDamage();		// Get function for returning the boss damage (since bossDamage is private)
	void setBossHealth(float);	// Used for changing bossHealth after the Player performs a damaging attack
	float getBossHealth();		// Used for returning the current value of the bossHealth
	void printHealthBars(Boss, Character);	// Function used in printing out the Health Bars for the Player & the Boss
	
	bool getCheckCrit();	// Returns the current value of the Critical Hit Check
	bool getCheckMiss();	// Returns the current value of the Attack Miss Check
private:
	bool bossCheckCrit;			// Variable that returns true during bossDetermineDamage if the Boss's attack is a critical hit
	bool bossCheckMiss;			// Variable that returns true during bossDetermineDamage if the Boss's attack misses
	float bossHealth;		// Current value for the Boss's health (initialized to 100)
	float bossDamage;		// Current value for the Boss's damaging attack (initialized after every bossDetermineDamage() call)
};