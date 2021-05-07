#include "Game.h"

Fire::Fire(int startX, int startY, float speed, int dir) : GameObject("Fire.png") {
	x = startX;
	y = startY;
	sprite.setPosition(x, y);
	this->dir = dir;
	this->speed = speed;
	type = Type::fire;
}

void Fire::Update() {
	y -= speed * dir;
	if (y < 0 || y > Game::Instance->WindowHeight) {
		Game::Instance->DelGameObject(this);
	}
	sprite.setPosition(x, y);
}

void Fire::Interspect(GameObject* obj)
{
	if (obj->type == Type::enemy) {
		Game::Instance->DelGameObject(this);
		Game::Instance->DelGameObject(obj);
	}
	if (obj->type == Type::wall) {
		Game::Instance->DelGameObject(this);
	}
	if (obj->type == Type::player) {
		Game::Instance->DelGameObject(this);
		Game::Instance->DelGameObject(obj);
	}
}

