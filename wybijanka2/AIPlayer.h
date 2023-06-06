#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "Player.h"

#include <unordered_map>
using namespace std;
class Plansza;

class AIPlayer : public Player {
private:
	bool isBialy;
	template <class T, class E>
	T getKeyByValue(unordered_map<T, E> map, E value);

public:

	AIPlayer(bool isBialy = false) { this->isBialy = isBialy; }
	virtual void getMoveee(Plansza& board);
};

#endif
