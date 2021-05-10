#include "pch.h"
#include "Game.h"
namespace SpaceInvaiders {
	Player::Player(int startX, int startY) : GameObject("Player.png") {
		x = startX;
		y = startY;
		sprite.setPosition(x, y);
		type = Type::player;
	}

	Player::~Player()
	{
		Game::Instance->DelTimer(shootTimer);
	}

	void Player::Update() {
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			left();
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			right();
		}
		if (shootTimer->IsTime()) {
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				fire();
			}
		}
		sprite.setPosition(x, y);
	}

	void Player::fire()
	{
		auto rect = sprite.getTextureRect();
		auto fire = new Fire(x + rect.width / 2 - 3, y - rect.height, 0.2f, 1, playerfire);
		Game::Instance->AddGameObject(fire);
		shootTimer->Restart();
	}

	void Player::right()
	{
		x += speed * Game::Instance->GetTime();
		auto rightBorder = Game::Instance->WindowWidth - sprite.getTextureRect().width;
		if (x > rightBorder) x = rightBorder;
	}

	void Player::left()
	{
		x -= speed * Game::Instance->GetTime();
		if (x < 0) x = 0;
	}

	void Player::Interspect(GameObject* obj)
	{
		if (obj->type == Type::enemyFire) {
			Game::Instance->DelGameObject(obj);
			Game::Instance->playerLives--;
			if (Game::Instance->playerLives == 0) {
				Game::Instance->Exit(lose);
			}
		}
	}
}