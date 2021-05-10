#include "pch.h"
#include "Game.h"

namespace SpaceInvaiders {
	Computer::Computer(int startX, int startY) : Player(startX, startY) {

	}

	void Computer::Update()
	{
		movePlayer();

		if (shootTimer->IsTime()) {
			fire();
		}
		sprite.setPosition(x, y);
	}

	void Computer::movePlayer()
	{
		float minPosX = Game::Instance->WindowWidth;
		for (auto enemy : Game::Instance->gameObjects) {//поиск крайнего бота
			if (enemy->type == Type::enemy) {
				if (minPosX > enemy->x) {
					minPosX = enemy->x;
				}
			}
		}
		for (auto fire : Game::Instance->gameObjects) {
			if (fire->type == Type::enemyFire) {
				if (isFireOnLine(fire->x, x, fireX) && isFireOnLine(fire->y, y, fireY)) {//если на предполагаемой линии снаряд
					left();
					return;
				}
			}
		}
		if (minPosX > x) {
			right();
			return;
		}
		if (minPosX < x) {
			left();
			return;
		}
	}

	bool Computer::isFireOnLine(float first, float second, int fireVisible) {
		auto sub = abs(first - second);
		return sub <= fireVisible;
	}
}