#include "Game.h"
#include <iostream>

using namespace std;

Enemy::Enemy(int startX, int startY) : GameObject("Enemy.png") {
	x = startX;
	y = startY;
	sprite.setPosition(x, y);
	type = Type::enemy;
	realX = x;
	shootTimer = new Timer(rand() % 4 + 3);
}

Enemy::~Enemy()
{
	Game::Instance->DelTimer(moveTimer);
}

void Enemy::Update() {
	if (moveTimer->IsTime()) {
		if (right) {
			if (x + radius <= realX) right = false;
			realX += speed;
		}
		else {
			if (x - radius >= realX) right = true;
			realX -= speed;
		}
		moveTimer->Restart();
	}
	sprite.setPosition(realX, y);
	if (shootTimer->IsTime()) {
		auto rect = sprite.getTextureRect();
		auto fire = new Fire(realX + rect.width / 2 - 3, y + rect.height + 5, 0.2f, -1, enemyFire);
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