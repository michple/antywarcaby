#include <array>
#include "Typedefs.h"
#include "Piece.h"

class Pionek;
class Ruch;

class Plansza {

public:
	const static int SIZE = 8;
private:
	Pionek* boardArray[SIZE][SIZE];
	void setValueAt(int x, int y, Pionek* pionek) {
		this->boardArray[y][x] = pionek;
	}
	void setValueAt(int position, Pionek* pionek);
	t_kordy getCoordsFromPos(int position);
public:
	Plansza();
	Plansza(Plansza& board);
	bool isPoleGry(int x, int y);
	int getPosFromKordy(int x, int y);
	Pionek* getPionekAt(int x, int y) { return this->boardArray[y][x]; }
	Pionek* getPionekAt(int position);
	bool pozaPlansza(int x, int y);
	bool pozaPlansza(int position);
	Pionek* ruchNaPlansze(t_ruch move, Pionek* pionek);
	Plansza(const Plansza& other) {

		for (int y = 0; y < SIZE; y++) {
			for (int x = 0; x < SIZE; x++) {
				if (other.boardArray[y][x] != nullptr) {
					boardArray[y][x] = new Pionek(x, y, getPionekAt(x, y)->isBialy);
				}
				else {
					boardArray[y][x] = nullptr;
				}
			}
		}
	};

};
