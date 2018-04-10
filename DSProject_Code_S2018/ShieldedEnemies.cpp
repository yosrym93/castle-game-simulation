#include "ShieldedEnemies.h"
ShieldedEnemies::ShieldedEnemies()
{
}

void ShieldedEnemies::addEnemy(Enemy * newEnemy)
{
	ShieldedArray.insert(newEnemy);
}
int ShieldedEnemies::getCount() const
{
	return ShieldedArray.getCount();
}

bool ShieldedEnemies::killRand()
{
	if (ShieldedArray.isEmpty())
		return false;

	Enemy* randomEnemy = ShieldedArray.pickRand();
	randomEnemy->setHealth(0);		//kills the enemy
	return true;
}

 bool ShieldedEnemies::isEmpty()
 {
	 return ShieldedArray.isEmpty();
 }
 void ShieldedEnemies::clear()
{
	ShieldedArray.clear();
}
 void ShieldedEnemies::update()
 {
	 ShieldedArray.update();
 }

string ShieldedEnemies::print()
 {
	 
	 int size = ShieldedArray.getCount();
	 Enemy* enemy;
	 string print;
	 for (int i = 0; i < size; i++)
	 {
		 enemy = ShieldedArray.get(i);
		 if (i != 0)
			 print = print + ", " + enemy->print();
		 else print = enemy->print();
	 }
	 return print;
 }
ShieldedEnemies::~ShieldedEnemies()
{
}