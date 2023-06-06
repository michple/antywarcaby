#include "Piece.h"

#include "Plansza.h"
#include "Ruch.h"
#include "Typedefs.h"

#include <iostream>

Pionek::Pionek(int x, int y, bool isBialy) {
	this->x = x;
	this->y = y;
	this->isBialy = isBialy;
}

t_kordy Pionek::getKordy() {
	t_kordy coords;
	coords[0] = this->x;
	coords[1] = this->y;
	return coords;
}

void Pionek::setDamka() {
	isDamka = true;
}

string Pionek::getString() {
	string baseSymbol;

	if (isBialy)
		baseSymbol = "W";
	else
		baseSymbol = "B";

	if (isDamka)
		baseSymbol += "K";
	else
		baseSymbol += " "; // add a space in the non-king state just to keep consistency

	return baseSymbol;
}

void Pionek::checkIfChangeToDamka(Plansza& board) {
	if (isBialy && this->y == Plansza::SIZE - 1 ||
		!isBialy && this->y == 0)
		setDamka();
}

t_ruchy_tab Pionek::getAllRuchy(Plansza& board) {
	t_ruchy_tab moves(0);
	int startingY, yIncrement;

	if (isBialy) {
		startingY = this->y + 1;
		yIncrement = -2;
	}
	else {
		startingY = this->y - 1;
		yIncrement = 2;
	}

	int rowsToCheck = 1;
	if (this->isDamka)
		rowsToCheck = 2;

	for (int x = this->x - 1; x <= this->x + 1; x += 2) {
		int y = startingY - yIncrement;
		for (int i = 0; i < rowsToCheck; i++) {
			y += yIncrement;
			if (board.pozaPlansza(x, y))
				continue;

			if (board.getPionekAt(x, y) == nullptr) {
				t_ruch move(new Ruch(this->x, this->y, x, y, nullptr, false));
				moves.push_back(move);
			}
		}
	}

	t_ruchy_tab possibleJumps = this->getAllBicia(board, nullptr);
	if (possibleJumps.size() != 0) {
		moves.clear();
		moves.insert(moves.begin(), possibleJumps.begin(), possibleJumps.end());
		moves.shrink_to_fit();
		return moves;
	}
	moves.insert(moves.end(), possibleJumps.begin(), possibleJumps.end());

	moves.shrink_to_fit();
	return moves;
}

t_ruchy_tab Pionek::getAllBicia(Plansza& board, t_ruch nextRuch) {
	t_ruchy_tab moves(0);
	int startingY, yIncrement;

	if (isBialy) {
		startingY = this->y + 2;
		yIncrement = -4;
	}
	else {
		startingY = this->y - 2;
		yIncrement = 4;
	}

	int rowsToCheck = 2;

	for (int x = this->x - 2; x <= this->x + 2; x += 4) {
		int y = startingY - yIncrement;
		for (int i = 0; i < rowsToCheck; i++) {
			y += yIncrement;
			if (board.pozaPlansza(x, y)) {
				continue;
			}

			if (nextRuch != nullptr && x == nextRuch->getFromKordy()[0] && y == nextRuch->getFromKordy()[1]) {
				continue;
			}

			Pionek* betweenPiece = board.getPionekAt((this->x + x) / 2, (this->y + y) / 2);
			if (betweenPiece != nullptr && betweenPiece->isBialy != this->isBialy && board.getPionekAt(x, y) == nullptr) {
				t_ruch jumpingMove(new Ruch(this->x, this->y, x, y, nextRuch, true));

				Pionek imaginaryPiece(x, y, this->isBialy);
				if (this->isDamka) imaginaryPiece.setDamka();
				t_ruchy_tab subsequentMoves = imaginaryPiece.getAllBicia(board, jumpingMove);
				moves.insert(moves.end(), subsequentMoves.begin(), subsequentMoves.end());

				if (subsequentMoves.size() == 0) {
					moves.push_back(jumpingMove);
				}
				//moves.insert(moves.end(), subsequentMoves.begin(), subsequentMoves.end());
			}
		}
	}
	moves.shrink_to_fit();
	return moves;
}
