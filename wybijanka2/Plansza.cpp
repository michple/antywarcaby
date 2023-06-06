#include "Plansza.h"
#include "Piece.h"
#include "Ruch.h"
#include "Typedefs.h"

Plansza::Plansza() {
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (y < 3 && isPoleGry(x, y)) {
				setValueAt(x, y, new Pionek(x, y, true));
			}
			else if (y >= SIZE - 3 && isPoleGry(x, y)) {
				setValueAt(x, y, new Pionek(x, y, false));
			}
			else {
				setValueAt(x, y, nullptr);
			}
		}
	}
}

Plansza::Plansza(Plansza& board) {
	for (int pos = 0; pos < SIZE * SIZE; pos++) {
		setValueAt(pos, board.getPionekAt(pos));
	}
}


Pionek* Plansza::ruchNaPlansze(t_ruch move, Pionek* pionek) {
	t_kordy moveStartingPos = pionek->getKordy();
	t_kordy moveEndingPos = move->getToKordy();
	vector<Pionek*> jumpedPieces = move->getZbitePionki(*this);
	if (!jumpedPieces.empty()) {
		for (unsigned int i = 0; i < jumpedPieces.size(); i++) {
			if (jumpedPieces[i] != nullptr) {
				setValueAt(jumpedPieces[i]->getKordy()[0], jumpedPieces[i]->getKordy()[1], nullptr);
			}
		}
	}
	setValueAt(moveStartingPos[0], moveStartingPos[1], nullptr);
	pionek->przesun(moveEndingPos[0], moveEndingPos[1]);
	pionek->checkIfChangeToDamka(*this);
	setValueAt(moveEndingPos[0], moveEndingPos[1], pionek);
	return getPionekAt(moveEndingPos[0], moveEndingPos[1]);
}

void Plansza::setValueAt(int position, Pionek* pionek) {
	t_kordy coords = getCoordsFromPos(position);
	setValueAt(coords[0], coords[1], pionek);
}
Pionek* Plansza::getPionekAt(int position) {
	t_kordy coords = getCoordsFromPos(position);
	return getPionekAt(coords[0], coords[1]);
}

t_kordy Plansza::getCoordsFromPos(int position) {
	t_kordy coords;
	coords[0] = position % SIZE;
	coords[1] = position / SIZE;
	return coords;
}

int Plansza::getPosFromKordy(int x, int y) {
	return SIZE * y + x;
}
bool Plansza::isPoleGry(int x, int y) {
	return x % 2 == y % 2;
}
bool Plansza::pozaPlansza(int x, int y) {
	return (x < 0 || x >= SIZE || y < 0 || y >= SIZE);
}

bool Plansza::pozaPlansza(int position) {
	t_kordy coords = getCoordsFromPos(position);
	return pozaPlansza(coords[0], coords[1]);
}

