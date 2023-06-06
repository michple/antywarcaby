#ifndef PLY_H
#define PLY_H

#include "Typedefs.h"
#include <vector>
#include <string>

class Plansza;
class Ruch;
class Pionek;

class Player {
private:
	bool isBialy;
	void pokazPlansze(Plansza& board, t_ruchy_tab possibleMoves);

	Pionek* getPionekFromUser(Plansza& board);
	t_ruch getMoveFromUser(t_ruchy_tab possibleMoves);
	string getKolor();

public:
	void pokazPlansze(Plansza& board);
	Player(bool isBialy = false) { this->isBialy = isBialy; }
	virtual void getMove(Plansza& board);
};

#endif
