#include "Game.h"
namespace Function {
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
				if (isFireOnLine(fire->x, x) && abs(y - fire->y) < 150) {//если на предполагаемой линии снаряд
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

	bool Computer::isFireOnLine(float first, float second) {
		auto sub = abs(first - second);
		return sub <= 75;
	}

	void Computer::fire()
	{
		auto rect = sprite.getTextureRect();
		auto fire = new Fire(x + rect.width / 2 - 3, y - rect.height, 0.2f, 1, playerfire);
		Game::Instance->AddGameObject(fire);
		shootTimer->Restart();
	}

	void Computer::right()
	{
		x += speed;
		auto rightBorder = Game::Instance->WindowWidth - sprite.getTextureRect().width;
		if (x > rightBorder) x = rightBorder;
	}

	void Computer::left()
	{
		x -= speed;
		if (x < 0) x = 0;
	}
}