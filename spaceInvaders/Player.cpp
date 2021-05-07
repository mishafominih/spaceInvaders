#include "Game.h"

Player::Player(int startX, int startY) : GameObject("Player.png") {
	x = startX;
	y = startY;
	sprite.setPosition(x, y);
	type = Type::player;
}

void Player::Update() {
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		x -= speed;
		if (x < 0) x = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		x += speed;
		auto rightBorder = Game::Instance->WindowWidth - sprite.getTextureRect().width;
		if (x > rightBorder) x = rightBorder;
	}
	if (shootTimer.IsTime()) {
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			auto rect = sprite.getTextureRect();
			auto fire = new Fire(x + rect.width / 2 - 3, y - rect.height, 0.2f, 1);
			Game::Instance->AddGameObject(fire);
			shootTimer.Restart();
		}
	}
	sprite.setPosition(x, y);
}

void Player::Interspect(GameObject* obj)
{
	if (obj->type == Type::fire) {
		Game::Instance->DelGameObject(this);
		Game::Instance->DelGameObject(obj);
	}
}
