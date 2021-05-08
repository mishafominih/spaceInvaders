#include "Game.h"
#include <iostream>

using namespace std;

Enemy::Enemy(int startX, int startY) : GameObject("Enemy.png") {
	x = startX;
	y = startY;
	sprite.setPosition(x, y);
	type = Type::enemy;
	realX = x;
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
}

void Enemy::Interspect(GameObject* obj) {
	if (obj->type == Type::fire) {
		Game::Instance->DelGameObject(this);
		Game::Instance->DelGameObject(obj);
	}
}