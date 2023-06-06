#include "Player.h"
#include "AIPlayer1.h"
#include "Player.h"
#include "Plansza.h"
#include "Piece.h"
#include "Ruch.h"

#include <vector>
#include <iostream>

bool isPlayer1 = true;
bool endGameNow = false;

void clearScreen() {
	cout << "\033[2J\033[1;1H";
}

void triggerEndGame() {
	endGameNow = true;
}

bool endGame(Plansza& board) {
	if (endGameNow) {
		return true;
	}
	else {
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
			cout << "REMIS" << endl;
		}
		else if (movableWhiteNum == 0) {
			cout << "BIALE WYGRALY" << endl;
		}
		else if (movableBlackNum == 0) {
			cout << "CZARNE WYGRALY" << endl;
		}
		else {
			return false;
		}
		return true;
	}
}

bool gameModeChoser() {
	while (true) {
		using namespace std;

		clearScreen();
		cout << "Wprowadz 'exit' aby zakonczyc gre\n" << '\n';
		cout << "Wybierz tryb gry" << '\n';
		cout << "[1] Gracz vs Komputer" << '\n';
		cout << "[2] 2 Graczy" << '\n';
		cout << "\nWprowadz liczbe " << '\n';

		string response;
		getline(cin, response);
		if (response == "1")
			return false;
		else if (response == "2")
			return true;
		else if (response == "exit") {
			triggerEndGame();
			return true;
		}
	}
}


int main() {
	Plansza board;


	if (gameModeChoser()) {
		Player* player1 = new Player(true);
		Player* player2 = new Player(false);
		clearScreen();

		while (!endGame(board)) {

			if (isPlayer1) {
				player1->getMove(board);
			}
			else {
				player2->getMove(board);
			}
			isPlayer1 = !isPlayer1;
		}
	}
	else {
		Player* player1 = new Player(true);
		AIPlayer* player2 = new AIPlayer(false);
		player2->isBialy = false;
		clearScreen();

		while (!endGame(board)) {

			if (isPlayer1) {
				player1->getMove(board);
			}
			else {
				player2->getMove(board);
			}
			isPlayer1 = !isPlayer1;
		}
	}

	return 0;
}

