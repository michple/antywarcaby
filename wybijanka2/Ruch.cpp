#include "Ruch.h"
#include "Piece.h"
#include "Plansza.h"
#include "Typedefs.h"

Ruch::Ruch(int x1, int y1, int x2, int y2, t_ruch nextRuch, bool isSkok) {
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	this->nextRuch = nextRuch;
	this->isSkok = isSkok;
}

t_kordy Ruch::getFromKordy() {
	t_kordy position;
	position[0] = x1;
	position[1] = y1;
	return position;
}

t_kordy Ruch::getToKordy() {
	t_kordy position;
	position[0] = x2;
	position[1] = y2;
	return position;
}

vector<Pionek*> Ruch::getZbitePionki(Plansza& board) {
	vector<Pionek*> pionki(0);
	if (isSkok) {
		int pionekX = (x1 + x2) / 2;
		int pionekY = (y1 + y2) / 2;
		pionki.push_back(board.getPionekAt(pionekX, pionekY));
		if (nextRuch != nullptr) {
			vector<Pionek*> prevJumped = nextRuch->getZbitePionki(board);
			pionki.insert(pionki.end(), prevJumped.begin(), prevJumped.end());
		}
	}
	pionki.shrink_to_fit();
	return pionki;
}
