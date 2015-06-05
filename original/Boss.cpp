// ECE 264 - Final Project
// Boss.cpp

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Master.h"
using namespace std;

Boss::Boss()	// Default constructor
{
	setBossHealth(100);		// Initializes Boss Health to 100
	setBossDamage(0);		// Initializes Boss Damage to 0 (just to initialize it to something -> bossDetermineDamage() will...
}							// ...randomly generate a value for the Damage value each time it is called)

int Boss::bossAttackType()
{
	int AttackType;
	AttackType = (rand()%5+1); // Initializes a random number between 1 and 2, where a 1 indicates a physical attack from the...
							   // ...boss and a 2 indicates a (fireball?) attack from the boss, etc...
	return AttackType;		   // Return the randomly generated value (used in combat script)
}

string Boss::printBossAttackType()
{
	int t = bossAttackType();
	if (t==1)
		return "deals a physical attack";
	if (t==2)
		return "casts a fireball spell";
	if (t==3)
		return "punches you in the groin";
	if (t==4)
		return "is taking in solar energy.....and casts Solar Beam";
	if (t==5)
		return "pokes you in the eye";
}

void Boss::bossCombatScript()
{
	// Determines the script based on what the Boss attack type is
	if ((getCheckCrit()==false)&&(getCheckMiss()==false))
		cout << "Boss " << printBossAttackType() << " for " << getBossDamage() << " damage" << endl;
	if (getCheckCrit()==true)	// If the Boss's attack is a critical hit
	{
		cout << "Boss " << printBossAttackType() << " for " << getBossDamage() << " damage\n";
		cout << "(Boss's attack is a critical hit!)" << endl;
	}
	else if (getCheckMiss()==true)	// If the Boss's attack has missed
		cout << "Boss's attack has missed, causing " << getBossDamage() << " damage" << endl;
	cout << "\n";
}

void Boss::setBossDamage(float bossDmg)
{
	bossDamage = bossDmg;
}

float Boss::getBossDamage()
{
	return bossDamage;
}

void Boss::setBossHealth(float health)
{
	bossHealth = health;
}

float Boss::getBossHealth()
{
	return bossHealth;
}

void Boss::bossDetermineDamage()
{
	int critChance, missChance; // Variables used for setting up the chances that the Boss either misses or successfully performs a critical hit 	
	bossCheckCrit = false;	// Initialize the Boss's critical hit chance to false
	bossCheckMiss = false;	// Initialize the Boss's miss chance to false
	critChance = (rand()%100+1); // Generates a random # used later in determining if the boss performed a critical hit
	missChance = (rand()%100+1); // Generates a random # used later in determining if the boss missed in his attack
	if ((1<=critChance)&&(critChance<=10))	// Creates a window of 10 out of 100 possible numbers, corresponding to a 10% chance of a...
	{										// ...boss critical hit
		bossCheckCrit = true;
	}
	if ((1<=missChance)&&(missChance<=10))	// Creates a window of 10 out of 100 possible numbers, corresponding to a 10% chance of a...
	{										// ...boss attack miss
		bossCheckMiss = true;
	}
	bossDamage = (rand()%10+1);	// Generates a random # between 1 and 10 corresponding to the amount of damage that the boss does
	if (bossCheckCrit && bossCheckMiss) // If the Critical Hit and Miss chances both return true
	{
		int decideCritOrMiss;	// Introduce a new integer that randomly decides whether the attack is a "Critical Hit" or "Miss"
		decideCritOrMiss = (rand()%2+1); // Randomly generate a number between 1 and 2 to determine the Boss Attack outcome
		if (decideCritOrMiss == 1)		 // If randomly generated # is 1...
			bossCheckCrit = true;		 // ...the Boss attack is treated as a Critical Hit
		else							 // If randomly generated # is 2...
			bossCheckMiss = true;		 // ...the Boss attack is treated as a Miss
	}									 
	if (bossCheckCrit)						 // If a boss critical hit is successful...
	{								      
		bossDamage = 1.5*bossDamage;	 // ...the new boss damage = (1.5 * [the # between 1 and 10 that was previously generated for bossDmg]).
	}						
	if (bossCheckMiss)						 // If the boss's attack misses the player during combat...
	{									  
		bossDamage = 0;					 // ...then the boss does 0 damage.
	}
}

bool Boss::getCheckCrit()
{
	return bossCheckCrit;
}

bool Boss::getCheckMiss()
{
	return bossCheckMiss;
}

void Boss::printHealthBars(Boss Boss1, Character Player)
{
	int pNumOfAst, bNumOfAst;
	float const PlayerMaxHealth = 100.0;
	float const BossMaxHealth = 100.0;

	cout << fixed << setw(5) << showpoint << setprecision(2);
	cout << " Player Health: " << Player.getCharacterHealth() << " / " << PlayerMaxHealth
		 << "        "
		 << "Boss Health: " << Boss1.getBossHealth() << " / " << BossMaxHealth << endl;
	cout << " ------------------------------- " << "    " << " ------------------------------- " << endl;
	pNumOfAst = (30*Player.getCharacterHealth()) / 100.0;
	bNumOfAst = (30*Boss1.getBossHealth()) / 100.0;
	cout << "|";
	for (int i=0; i<=pNumOfAst; i++)
	{
		cout << "*";	
	}
	for (int j=0; j<=(29-pNumOfAst);j++)
	{
		cout << " ";
	}
	cout << "|" << "    " << "|";
	for (int i=0; i<=bNumOfAst; i++)
	{
		cout << "*";	
	}
	for (int j=0; j<=(29-bNumOfAst);j++)
	{
		cout << " ";
	}
	cout << "|" << endl;
	cout << " ------------------------------- " << "    " << " ------------------------------- " << endl;
	cout << "\n";
}