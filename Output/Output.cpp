#include "Output.h"
#include <fstream>
#include "..\Battle.h"

using namespace std;


Output::Output()
{
	sumFD = 0;
	sumKD = 0;
	nKilled = 0;
	nEnemies = 0;

	//Write the first line in the file
	ofstream writer;
	writer.open("game_output.txt", ios::trunc);

	if (writer.is_open()) 
		writer << "KTS" << '\t' << "S" << '\t' << "FD" << '\t' << "KD" << '\t' << "LT" << endl;

	writer.close();
}

void Output::addEnemy(Enemy* e) {
	enemiesList.insert(e);
	sumFD += e->getFD();
	sumKD += e->getKD();
	nKilled++;
}

void Output::writeEnemy(Enemy* e, int currTime) {
	ofstream writer;
	writer.open("game_output.txt", ios::app);

	if (writer.is_open()) {
		int S = e->getId(), FD = e->getFD(), KD = e->getKD();
		int LT = FD + KD;
		writer << currTime << '\t' << S << '\t' << FD << '\t' << KD << '\t' << LT << endl;
	}
	writer.close();
}

void Output::writeEnemies(Battle &b) {
	
	enemiesList.sort(&Enemy::getFD);

	enemiesList.traverse(&Battle::writeEnemy, b);	//Writes enemies data
	enemiesList.clear();							//Deletes the enemies
}

void Output::writeGameStatus(Battle &b) {
	ofstream writer;
	writer.open("game_output.txt", ios::app);

	if (writer.is_open()) {
		writer << endl;

		//Writing total tower damage taken
		
		writer << "T1_Total_Damage" << '\t' << "T2_Total_Damage" << '\t' << "T3_Total_Damage" << '\t' 
			<< "T4_Total_Damage" << endl;

		for (int i = 0; i < NoOfRegions; i++) {
			double towerDamage = towerStartingHealth - b.getTowerHealth(i);
			writer << towerDamage << '\t' << '\t';
		}
		writer << endl << endl;
		//Writing unpaved distances
		writer << "R1_Unpaved_Dist" << '\t' << "R2_Unpaved_Dist" << '\t' << "R3_Unpaved_Dist" << '\t'
			<< "R4_Unpaved_Dist" << endl;

		for (int i = 0; i < NoOfRegions; i++) 
			writer << b.getUnpavedDist(i) << '\t' << '\t';

		writer << endl << endl;

		//Writing final game status

		double averageFD = double(sumFD) / double(nKilled);
		double averageKD = double(sumKD) / double(nKilled);

		if (b.getGameStatus() == WIN) {	
			writer << "Game is WIN !" << endl << endl;
			writer << "Total number of enemies: " << nEnemies << endl;
		}
		else {
			writer << "Game is LOSS !" << endl << endl;
			writer << "Total number of killed enemies: " << nKilled << endl;
			writer << "Total Number of alive: " << nEnemies - nKilled << endl;
		}

		writer << "Average First-shot delay: " << averageFD << endl;
		writer << "Average kill delay: " << averageKD << endl;

	}
	writer.close();
}

void Output::setTotalEnemies(int n) {
	nEnemies = n;
}

void Output::setTowerStartingHealth(double h) {
	towerStartingHealth = h;
}

void Output::reset() {
	//Open the file to truncate it and write the first line
	ofstream writer;
	writer.open("game_output.txt", ios::trunc);

	if (writer.is_open())
		writer << "KTS" << '\t' << "S" << '\t' << "FD" << '\t' << "KD" << '\t' << "LT" << endl;

	writer.close();

	enemiesList.clear();
}

Output::~Output()
{
}
