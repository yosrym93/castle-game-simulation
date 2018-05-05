#pragma once
class Battle;
class Tower
{
	double health;
	int N; // max number of elements tower can attack in time step
	int firePower;
	bool isKilled;
	bool canAttack;
	int freezeTime;		//attack time of freeze tank

public:
	Tower();
	//setter and getters..
	void setHealth(double h);
	double getHealth() const;
	void setNum(int );
	void setFirePower(int );
	int getMaxNum()const;
	int getFirePower()const;
	void damage(double);		//decrease tower health
	bool isDestroyed()const;		//returns true when tower is completely damaged
	bool getCanAttack(int)const;		//returns false during freezeTank attack time - USE CURRENT TIME AS A PARAMETER
	void freeze(int);					//freeze the tower during freezeTank attack time 


};

