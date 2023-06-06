#include "Player.h"
#include "Plansza.h"
#include "Ruch.h"
#include "Piece.h"
#include "Typedefs.h"
#include <array>
#include <exception>
#include <iostream>
#include <cassert>

void clearScreen();
void triggerEndGame();

void Player::getMove(Plansza& board) {
	pokazPlansze(board);
	t_ruchy_tab possibleMoves;
	while (true) {
		Pionek* pieceMoving = getPionekFromUser(board);
		if (pieceMoving == nullptr) {
			return;
		}
		possibleMoves = pieceMoving->getAllRuchy(board);

		if (possibleMoves.empty())
			cout << "Pionek nie ma mozliwozci ruchu. Wybierz inny:" << '\n';
		else {
			pokazPlansze(board, possibleMoves);
			t_ruch move = getMoveFromUser(possibleMoves);

			if (move != nullptr) {
				Pionek* p = board.ruchNaPlansze(move, pieceMoving);
				return;
			}
		}
	}
}

void Player::pokazPlansze(Plansza& board, t_ruchy_tab possibleMoves) {
	clearScreen();
	for (int y = -1; y < Plansza::SIZE; y++) {
		for (int x = -1; x < Plansza::SIZE; x++) {
			if (y == -1) {
				if (x != -1)
					cout << "-" << (char)(x + 65) << "- ";
				else
					cout << "     ";
			}
			else if (x == -1) {
				if (y != -1)
					cout << "-" << y + 1 << "- ";
			}
			else {
				Pionek* thisPiece = board.getPionekAt(x, y);

				if (!possibleMoves.empty()) {
					bool moveFound = false;

					for (unsigned int i = 0; i < possibleMoves.size(); i++) {
						t_kordy move = possibleMoves[i]->getToKordy();
						if (move[0] == x && move[1] == y) {
							std::cout << "| " << i + 1 << " ";
							moveFound = true;
						}
					}

					if (moveFound)
						continue;
				}

				if (thisPiece != nullptr)
					std::cout << "| " << thisPiece->getString();
				else if (board.isPoleGry(x, y))
					std::cout << "| . ";
				else
					std::cout << "|   ";
			}
		}
		cout << '\n';
	}
}

void Player::pokazPlansze(Plansza& board) {
	static t_ruchy_tab emptyPossibleMoves(0);
	pokazPlansze(board, emptyPossibleMoves);
}


Pionek* Player::getPionekFromUser(Plansza& board) {
	while (true) {
		using namespace std;
		string raw;
		cin.clear();
		fflush(stdin);
		cout << getKolor() << ", wybierz pionka do ruchu np (e3):" << '\n';
		try {
			getline(cin, raw);
			if (raw == "exit") {
				triggerEndGame();
				return nullptr;
			}
			else if (raw.length() < 2) {
				throw ("Wybierz pionka do ruchu np (e3)");
			}
			char letterChar = raw[0];
			char numberChar = raw[1];
			if (isdigit(letterChar)) {
				letterChar = numberChar;
				numberChar = raw[0];
			}
			int x = letterChar - 97;
			int y = numberChar - 48 - 1;

			if (board.pozaPlansza(x, y)) {
				throw ("Wspolrzedne poza plasza");
			}
			Pionek* userPiece = board.getPionekAt(x, y);
			if (userPiece == nullptr) {
				cout << "Brak pionka!!! \n";
			}
			else if (userPiece->isBialy != this->isBialy) {
				cout << "Pionek przeciwnika!!! Wybierz swoj\n";
			}
			else {
				return board.getPionekAt(x, y);
			}
			cin.clear();
			fflush(stdin);
		}
		catch (const char* e) {
			cout << e << '\n';
			cin.clear();
			fflush(stdin);
		}
	}
}

t_ruch Player::getMoveFromUser(t_ruchy_tab possibleMoves) {
	int moveNum;

	while (true) {
		using namespace std;
		cout << getKolor() << ", wybierz ktory ruch chcesz wykonac. Podaj liczbe np (1) ";
		try {

			cin >> moveNum;

			if (!cin.good()) {
				cin.ignore(256, '\n');
				throw ("Podaj liczbe.");
			}

			else if (moveNum > possibleMoves.size()) {
				cin.ignore(256, '\n');
				throw ("Wybierz ruch widoczne na planszy lub 0 aby wybrac inny pionek");
			}
			else if (moveNum == 0) {
				return nullptr;
			}
			cin.ignore(256, '\n');
			return possibleMoves[moveNum - 1];
		}
		catch (const char* e) {
			cout << e << '\n';
			cin.clear();
			cin.ignore(256, '\n');
			fflush(stdin);
		}
	}
}

string Player::getKolor() {
	return isBialy?"Biale":"Czarne";
}
