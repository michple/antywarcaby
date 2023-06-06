#include <array>
#include <vector>
#include "Typedefs.h"

class Pionek;
class Plansza;

class Ruch {
private:
	int x1, y1, x2, y2;
	t_ruch nextRuch;
	bool isSkok;

public:
	Ruch(int x1, int y1, int x2, int y2, t_ruch nextRuch, bool isSkok);
	t_kordy getFromKordy();
	t_kordy getToKordy();
	vector<Pionek*> getZbitePionki(Plansza& board);
	void wypisz() {
		if (this != nullptr) {
			std::cout << " x1: " << x1 << " y1: " << y1 << " x2: " << x2 << " y2: " << y2 << "\n";
		}
		else {
			std::cout << "Ruch null \n";
		}

	}
};


