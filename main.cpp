#include "Battle.h"
#include "GUI\GUI.h"
void Simulation(Battle *B, GUI *G);

int main()
{
	Battle* pGameBattle = new Battle;
	GUI * pGUI = new GUI;
	pGameBattle->startBattle(pGUI);

	delete pGUI;
	delete pGameBattle;
	
	return 0;
}

void Simulation(Battle *pGameBattle,GUI *pGUI)
{
	Point p;
	string msg;
	int TimeStep = 0;
	while (pGameBattle->isFighting())
	{
		pGUI->GetPointClicked(p);
		// Clear for redrawing
		pGUI->ClearStatusBar();
		pGUI->ClearBattleArea();
		pGUI->DrawCastle();
		pGameBattle->update();
		//printing info
		pGameBattle->print(pGUI);
		// Redraw the enemies
		pGameBattle->drawEnemies(pGUI);
	//	pGameBattle->killRandom();

		TimeStep++;
	}

	pGUI->GetPointClicked(p);
	
}
