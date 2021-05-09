#include "Game.h"
#include <iostream>

using namespace std;
using namespace Function;

int main() {
	setlocale(0, "");
	cout << "¬ведите 0 что бы играть самому, 1 что бы сыграл компьютер" << endl;
	int input;
	cin >> input;
	float speedShoot = 0;
	while (true) {
		auto game = Game(speedShoot, input == 0);
		if (Game::result == exite) return 0;
		if (Game::result == win) speedShoot += 0.8;
		if (Game::result == lose) speedShoot -= 0.8;
	}
}