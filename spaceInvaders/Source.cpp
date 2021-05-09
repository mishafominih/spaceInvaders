#include "Game.h"
#include <iostream>

using namespace std;

int main() {
	float speedShoot = 0;
	while (true) {
		auto game = Game(speedShoot);
		if (Game::result == exite) return 0;
		if (Game::result == win) speedShoot += 0.8;
		if (Game::result == lose) speedShoot = 0;
	}
}