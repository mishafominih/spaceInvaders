#include "Game.h"

Wall::Wall(int startX, int startY) : GameObject("Wall.png") {
	x = startX;
	y = startY;
	sprite.setPosition(x, y);
	type = Type::enemy;
}


void Wall::Interspect(GameObject* obj)
{
	if (obj->type == Type::playerfire || obj->type == Type::enemyFire) {
		Game::Instance->DelGameObject(obj);
	}
}