#include "Game.h"

Enemy::Enemy(int startX, int startY) : GameObject("Enemy.png") {
	x = startX;
	y = startY;
	sprite.setPosition(x, y);
	type = Type::enemy;
}

void Enemy::Update() {
	sprite.setPosition(x, y);
}

void Enemy::Interspect(GameObject* obj) {
	if (obj->type == Type::fire) {
		Game::Instance->DelGameObject(this);
		Game::Instance->DelGameObject(obj);
	}
}