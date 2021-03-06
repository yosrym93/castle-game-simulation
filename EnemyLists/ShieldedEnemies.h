#pragma once
#include "..\Enemies\Enemy.h"
#include "..\ADTs\Array.h"
#include "../Castle/Tower.h"

class Battle;

class ShieldedEnemies
{
	Array<Enemy> ShieldedArray;
public:
	ShieldedEnemies();
	int getCount() const;
	void addEnemy(Enemy* newEnemy);
	void clear();
	bool killRand();			//for phase 1: picks a random enemy and sets its health to zero.
	bool isEmpty();
	void importOther(ShieldedEnemies&);	//Moves enemies from one region to another	
	void removeKilled(Battle &);		//Removes killed enemies from the list and calls Battles' killEnemy(killedEnemy)
	~ShieldedEnemies();
	string print();
	void enemiesAttack(Battle*);			//traverse the list to call attack for each enemy
	void enemiesMove(Battle*);			//traverse the list to call move for each enemy
	void enemiesHeal(int* A);					//traverse the list to call heal for each enemy
	void enemiesTravel(int n,int d);		//traverses the list to move them from region to region
	void towerAttack(Tower*, int);			//traverse the list to attack the enemies by the tower
	void calcPriority(Battle*);				//calculate the priority of the shielded enemies
};

