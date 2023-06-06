#include "AIPlayer.h"

#include "Plansza.h"
#include "Piece.h"
#include "Ruch.h"
#include "Typedefs.h"

#include <unordered_map>
#include <vector>
#include <cstdlib>

void AIPlayer::getMoveee(Plansza& board) {
	using namespace std;
	typedef unordered_map<Pionek*, t_ruchy_tab> move_choices_tab;
	typedef unordered_map<t_ruch, Pionek*> best_moves_tab;
	move_choices_tab mozliweWybory;
	// wybieram pionki którymi moge sie ruszyc
	for (int x = 0; x < Plansza::SIZE; x++) {
		for (int y = 0; y < Plansza::SIZE; y++) {
			Pionek* pionek = board.getPionekAt(x, y);
			if (pionek != nullptr && pionek->isBialy == this->isBialy) {
				t_ruchy_tab pionekPossibleMoves = pionek->getAllRuchy(board);
				if (!pionekPossibleMoves.empty())
					mozliweWybory[pionek] = pionekPossibleMoves;
			}
		}
	}
	Pionek* furthestBackwardPiece = mozliweWybory.begin()->first;
	Pionek* furthestForwardPiece = mozliweWybory.begin()->first;

	best_moves_tab bestMovesPerPiece;
	for (auto wybor : mozliweWybory) {
		Pionek* pionek = wybor.first;
		int thisPieceY = pionek->getKordy()[1];
		if (thisPieceY > furthestForwardPiece->getKordy()[1]) {
			if (isBialy){
				furthestForwardPiece = pionek;
			}
			else{
				furthestBackwardPiece = pionek;
			}
		}
		else if (thisPieceY < furthestBackwardPiece->getKordy()[1]) {
			if (isBialy){
				furthestBackwardPiece = pionek;
			}
			else{
				furthestForwardPiece = pionek;
			}
		}
		// wybieram ruch pionka który może zbić najwięcej
		t_ruchy_tab possibleMoves = mozliweWybory[pionek];
		t_ruch maxJumpMove = possibleMoves[0];
		int maxJumpMoveLength = 0;
		for (unsigned int i = 0; i < possibleMoves.size(); i++) {
			vector<Pionek*> jumpedPieces = possibleMoves[i]->getZbitePionki(board);
			if (!jumpedPieces.empty()) {
				int jumpLength = jumpedPieces.size();
				if (jumpLength >= maxJumpMoveLength) {
					maxJumpMoveLength = jumpLength;
					maxJumpMove = possibleMoves[i];
				}
			}
		}
		bestMovesPerPiece[maxJumpMove] = pionek;
	}
	// wybieram najlepszego pionka który zbije najwięcej
	t_ruch absoluteBestMove = bestMovesPerPiece.begin()->first;
	int absoluteBestMoveJumpLength = 0;
	for (auto it : bestMovesPerPiece) {
		t_ruch move = it.first;
		vector<Pionek*> jumpedPieces = move->getZbitePionki(board);
		if (!jumpedPieces.empty()) {
			int thisBestMoveJumpLength = jumpedPieces.size();
			if (thisBestMoveJumpLength >= absoluteBestMoveJumpLength) {
				absoluteBestMoveJumpLength = thisBestMoveJumpLength;
				absoluteBestMove = move;
			}
		}
	}
	if (absoluteBestMoveJumpLength > 0) {
		board.ruchNaPlansze(absoluteBestMove, bestMovesPerPiece[absoluteBestMove]);
	}
	else {
		int randomNum = rand() & 100;
		if (randomNum >= 50) {
			board.ruchNaPlansze(getKeyByValue(bestMovesPerPiece, furthestBackwardPiece), furthestBackwardPiece);
		}
		else {
			board.ruchNaPlansze(getKeyByValue(bestMovesPerPiece, furthestForwardPiece), furthestForwardPiece);
		}
	}
}

template <class T, class E>
T AIPlayer::getKeyByValue(unordered_map<T, E> map, E value) {
	for (auto it : map) {
		if (it.second == value) {
			return it.first;
		}
	}
	return nullptr;
}
