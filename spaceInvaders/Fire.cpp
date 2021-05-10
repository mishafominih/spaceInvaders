#include "pch.h"
#include "Game.h"

namespace SpaceInvaiders {
	Fire::Fire(int startX, int startY, float speed, int dir, Type type) : GameObject("Fire.png") {
		x = startX;
		y = startY;
		sprite.setPosition(x, y);
		this->dir = dir;
		this->speed = speed;
		this->type = type;
	}

	void Fire::Update() {
		y -= speed * dir * Game::Instance->GetTime();
		if (y < 0 || y > Game::Instance->WindowHeight) {
			Game::Instance->DelGameObject(this);
		}
		sprite.setPosition(x, y);
	}

	void Fire::Interspect(GameObject* obj)
	{
		if(obj->type != playerfire && obj->type != enemyFire)
			obj->Interspect(this);
	}
}
