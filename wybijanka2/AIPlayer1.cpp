#include "AIPlayer1.h"

#include "Plansza.h"
#include "Piece.h"
#include "Ruch.h"
#include "Typedefs.h"

#include <limits>
#include <unordered_map>
#include <limits>


void AIPlayer::getMove(Plansza& board) {
	int maxDepth = 2;
	int bestScore = -1000000;
	shared_ptr<Ruch> bestMove = nullptr;
	Pionek* pieceBest = nullptr;

	for (int x = 0; x < Plansza::SIZE; x++) {
		for (int y = 0; y < Plansza::SIZE; y++) {
			Pionek* piece = board.getPionekAt(x, y);
			if (piece != nullptr && piece->isBialy == this->isBialy) {
				t_ruchy_tab piecePossibleMoves = piece->getAllRuchy(board);
				for (auto& move : piecePossibleMoves) {
					Plansza newBoard = Plansza(board);
					Pionek* p = new Pionek(piece->getx(), piece->gety(), piece->isBialy);
					int score = minmax(newBoard, maxDepth, p, move, board);
					if (score > bestScore) {
						bestScore = score;
						pieceBest = piece;
						bestMove = move;
					}
				}
			}
		}
	}
	board.ruchNaPlansze(bestMove, pieceBest);
}

int AIPlayer::minmax(Plansza& board, int depth, Pionek* p, shared_ptr<Ruch> ruch, Plansza& orgBoard) {

	if (depth == 0 || enddGame(board)) {
		return evaluate(board, orgBoard, p->isBialy);
	}

	if (p->isBialy) {
		int maxEval = INT_MIN;

		Plansza newBoard = Plansza(board);
		Pionek* tmp = new Pionek(p->getx(), p->gety(), p->isBialy);
		Pionek* pieceMoved = newBoard.ruchNaPlansze(ruch, tmp);

		for (int x = 0; x < Plansza::SIZE; x++) {
			for (int y = 0; y < Plansza::SIZE; y++) {
				Pionek* piece = board.getPionekAt(x, y);
				if (piece != nullptr && piece->isBialy == !this->isBialy) {
					t_ruchy_tab possibleMoves = piece->getAllRuchy(board);
					for (const auto& move : possibleMoves) {
						Pionek* tmp1 = new Pionek(piece->getx(), piece->gety(), piece->isBialy);
						Plansza newBoard1 = Plansza(newBoard);

						int eval = minmax(newBoard, depth - 1, pieceMoved, move, orgBoard);
						eval += evaluate(newBoard, orgBoard, tmp1->isBialy) * (aiDepth - (aiDepth - depth));
						maxEval = max(maxEval, eval);
					}
				}
			}
		}
		return maxEval;
	}
	else {
		int minEval = INT_MAX;

		Plansza newBoard = Plansza(board);
		Pionek* tmp = new Pionek(p->getx(), p->gety(), p->isBialy);
		Pionek* pieceMoved = newBoard.ruchNaPlansze(ruch, tmp);

		for (int x = 0; x < Plansza::SIZE; x++) {
			for (int y = 0; y < Plansza::SIZE; y++) {
				Pionek* piece = board.getPionekAt(x, y);
				if (piece != nullptr && piece->isBialy == !this->isBialy) {

					t_ruchy_tab possibleMoves = piece->getAllRuchy(board);
					for (const auto& move : possibleMoves) {
						Pionek* tmp1 = new Pionek(piece->getx(), piece->gety(), piece->isBialy);
						Plansza newBoard1 = Plansza(newBoard);

						int eval = minmax(newBoard1, depth - 1, tmp1, move, orgBoard);
						eval += evaluate(newBoard, orgBoard, tmp1->isBialy) * (aiDepth - (aiDepth - depth));
						minEval = min(minEval, eval);
					}
				}
			}
		}
		return minEval;
	}
}


int AIPlayer::evaluate(Plansza& board, Plansza& orgBoard, bool isBialy) {

	int orgplayerBialy = 0;
	int orgplayerczarny = 0;

	for (int x = 0; x < Plansza::SIZE; x++) {
		for (int y = 0; y < Plansza::SIZE; y++) {
			Pionek* pionek = orgBoard.getPionekAt(x, y);
			if (pionek != nullptr) {
				if (pionek->isBialy) {
					orgplayerBialy++;
				}
				else {
					orgplayerczarny++;
				}
			}
		}
	}

	int playerBialy = 0;
	int playerczarny = 0;

	for (int x = 0; x < Plansza::SIZE; x++) {
		for (int y = 0; y < Plansza::SIZE; y++) {
			Pionek* pionek = board.getPionekAt(x, y);
			if (pionek != nullptr) {
				if (pionek->isBialy) {
					playerBialy++;
				}
				else {
					playerczarny++;
				}
			}
		}
	}

	if ((playerBialy + playerczarny) == (orgplayerBialy + orgplayerczarny)) {
		return 2;
	}

	int sum = 0;
	int czardiff = orgplayerczarny - playerczarny;
	int bialdiff = orgplayerBialy - playerBialy;

	if (isBialy) {
		sum = (czardiff * 1000) + (bialdiff * 100);
		return sum;
	}
	else {
		sum = (bialdiff * 1000) + (czardiff * 100);
		return sum;
	}

}


bool AIPlayer::enddGame(Plansza& board) {
	int movableWhiteNum = 0;
	int movableBlackNum = 0;
	for (int pos = 0; pos < Plansza::SIZE * Plansza::SIZE; pos++) {
		Pionek* pieceHere = board.getPionekAt(pos);
		if (pieceHere != nullptr) {
			if (!pieceHere->getAllRuchy(board).empty()) {
				if (pieceHere->isBialy) {
					movableWhiteNum++;
				}
				else {
					movableBlackNum++;
				}
			}
		}
	}

	using namespace std;
	if (movableWhiteNum + movableBlackNum == 0) {
		return true;
	}
	else if (movableWhiteNum == 0) {
		return true;
	}
	else if (movableBlackNum == 0) {
		return true;
	}
	else {
		return false;
	}
}

void AIPlayer::countPionki(Plansza& board) {
	int playerBialy = 0;
	int playerczarnyy = 0;
	for (int x = 0; x < Plansza::SIZE; x++) {
		for (int y = 0; y < Plansza::SIZE; y++) {
			Pionek* pionek = board.getPionekAt(x, y);
			if (pionek != nullptr) {
				if (pionek->isBialy) {
					playerBialy++;
				}
				else {
					playerczarnyy++;
				}
			}
		}
	}
}