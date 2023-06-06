#ifndef PIONEK_H
#define PIONEK_H

#include <string>
#include <vector>
#include <array>
#include "Typedefs.h"

class Plansza;
class Ruch;

class Pionek {
private:
	int x;
	int y;
	bool isDamka = false;
	void setDamka();
	t_ruchy_tab getAllBicia(Plansza& board, t_ruch nextRuch);

public:
	bool isBialy;
	Pionek(int x, int y, bool isBialy);
	t_kordy getKordy();
	string getString();
	void checkIfChangeToDamka(Plansza& board);
	void przesun(int x, int y) { this->x = x; this->y = y; }
	t_ruchy_tab getAllRuchy(Plansza& board);
	int getx() { return x; }
	int gety() { return y; }
	void wypisz() {
		if (this != nullptr) {
			std::cout << " x: " << x << " y: " << y << "\n";
		}
		else {
			std::cout << " pionek null \n";
		}
	}
};

#endif
