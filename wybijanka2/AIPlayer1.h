#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
#include <algorithm>

class AIPlayer: public Player {
public:
	bool isBialy;
	int aiDepth = 5;
	AIPlayer(bool isBialyy = false) { Player(); };
	void getMove(Plansza& board);

	int evaluate(Plansza& board, Plansza& orgBoard, bool isBialy);

private:
	int minmax(Plansza& board, int depth, Pionek* p, t_ruch ruch, Plansza& orgBoard);
	void countPionki(Plansza& board);
	bool enddGame(Plansza& board);
};

#endif