#include "Game.h"
#include <iostream>

using namespace std;
using namespace SpaceInvaiders;

int main() {
	setlocale(0, "");
	cout << "������� 0 ��� �� ������ ������, 1 ��� �� ������ ���������" << endl;
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