#include <SFML/Graphics.hpp>
#include <time.h>
#include "Game.h"
#include <iostream>

using namespace std;
namespace Function {

	Game* Game::Instance;
	Result Game::result;

	Game::Game(float speedShoot, bool isPlayer) {
		if (speedShoot >= 3) {
			cout << "You Win!!!" << endl;
			Exit(exite);
		}
		this->speedShoot = speedShoot;
		Instance = this;
		RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "battle city 2");

		SetPlayer(isPlayer);
		CreateEnemy();
		CreateWall();

		Clock clock;
		srand(std::time(0));
		auto life = new GameObject("Player.png");

		Font font = Font();
		font.loadFromFile("CyrilicOld.ttf");

		Text lives = Text("Lives:", font, 25);
		lives.setPosition(WindowWidth - 400, 25);
		while (window.isOpen())
		{
			time = clock.getElapsedTime().asSeconds();
			clock.restart();
			for (int i = 0; i < timers.size(); i++) {//итерация таймеров
				timers[i]->Tick(time);
			}

			for (int i = 0; i < gameObjects.size(); i++) {//обновление состояний игровых объектов
				gameObjects[i]->Update();
			}

			CheckInterspect();

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					Exit(Result::exite);
				}
			}
			window.clear();

			int count = 0;
			for (int i = 0; i < gameObjects.size(); i++) {
				if (gameObjects[i]->type == Type::enemy) {
					count++;
				}
			}
			if (count == 0)
				Exit(win);

			for (int i = 0; i < gameObjects.size(); i++) {
				window.draw(gameObjects[i]->sprite);
			}
			for (int i = 0; i < playerLives; i++) {
				life->sprite.setPosition(WindowWidth - 300 + 75 * i, 0);
				window.draw(life->sprite);
			}
			window.draw(lives);
			window.display();
			if (exit) {
				window.close();
			}
		}
	}

	void Game::SetPlayer(bool isPlayer)
	{
		GameObject* player = nullptr;
		if (isPlayer)
			player = new Player(WindowWidth / 2, WindowHeight - 100);
		else
			player = new Computer(WindowWidth / 2, WindowHeight - 100);
		AddGameObject(player);
	}

	void Game::CheckBots()
	{

	}

	void Game::Exit(Result res)
	{
		result = res;
		exit = true;
	}

	void Game::CreateWall()
	{
		auto countWall = 4;
		for (int i = 0; i < countWall; i++) {
			auto wall = new Wall(WindowWidth / countWall * i, WindowHeight - 260);
			AddGameObject(wall);
		}
	}

	void Game::CheckInterspect()
	{
		for (int i = 0; i < gameObjects.size(); i++) {
			for (int j = i + 1; j < gameObjects.size(); j++) {
				auto first = gameObjects[i];
				auto second = gameObjects[j];
				auto interspect = first->sprite.getGlobalBounds().intersects(second->sprite.getGlobalBounds());
				if (interspect) {
					first->Interspect(second);
					//second->Interspect(first);
				}
			}
		}
	}

	void Game::CreateEnemy() {
		auto horizontalCount = 10;
		auto verticalCount = 3;
		for (int i = 0; i < horizontalCount; i++) {
			for (int j = 0; j < verticalCount; j++) {
				auto enemy = new Enemy(
					WindowWidth / (horizontalCount + 1) * (i + 1),
					(WindowHeight - 300) / (verticalCount + 1) * (j + 1));
				AddGameObject(enemy);
			}
		}
	}

	void Game::AddGameObject(GameObject* obj) {
		obj->index = gameObjects.size();
		gameObjects.push_back(obj);
	}

	void Game::DelGameObject(GameObject* obj) {
		auto iter = gameObjects.cbegin(); // указатель на удаляемый элемент
		for (int i = obj->index + 1; i < gameObjects.size(); i++) {
			gameObjects[i]->index--;
		}
		gameObjects.erase(iter + obj->index);   // удаляем третий элемент
		delete obj;
	}

	void Game::AddTimer(Timer* timer)
	{
		timer->index = timers.size();
		timers.push_back(timer);
	}

	void Game::DelTimer(Timer* timer)
	{
		auto iter = timers.cbegin(); // указатель на удаляемый элемент
		for (int i = timer->index + 1; i < timers.size(); i++) {
			timers[i]->index--;
		}
		timers.erase(iter + timer->index);   // удаляем третий элемент
		delete timer;
	}
}