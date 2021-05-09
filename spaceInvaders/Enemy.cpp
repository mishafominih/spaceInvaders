#include "pch.h"
#include "Game.h"
#include <iostream>

using namespace std;
namespace Function {
	Enemy::Enemy(int startX, int startY) : GameObject("Enemy.png") {
		x = startX;
		y = startY;
		sprite.setPosition(x, y);
		type = Type::enemy;
		this->startX = x;
		shootTimer = new Timer(rand() % 4 + 3 - Game::Instance->speedShoot);
	}

	Enemy::~Enemy()
	{
		Game::Instance->DelTimer(moveTimer);
	}

	void Enemy::Update() {
		if (moveTimer->IsTime()) {
			if (right) {
				if (startX + radius <= x) right = false;
				x += speed * Game::Instance->time * 1400;
			}
			else {
				if (startX - radius >= x) right = true;
				x -= speed * Game::Instance->time * 1400;
			}
			moveTimer->Restart();
		}
		sprite.setPosition(x, y);
		if (shootTimer->IsTime()) {
			auto rect = sprite.getTextureRect();
			auto fire = new Fire(x + rect.width / 2 - 3, y + rect.height + 5, 0.2f, -1, enemyFire);
			Game::Instance->AddGameObject(fire);
			shootTimer->Restart();
		}
	}

	void Enemy::Interspect(GameObject* obj) {
		if (obj->type == Type::playerfire) {
			Game::Instance->DelGameObject(this);
			Game::Instance->DelGameObject(obj);
		}
	}
}