#include <SFML/Graphics.hpp>
#include <time.h>
#include "Game.h"

Game* Game::Instance;

Game::Game() {
	Instance = this;
	RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "battle city 2");
	auto pl = new Player(WindowWidth / 2, WindowHeight - 100);
	AddGameObject(pl);
	CreateEnemy();
	CreateWall();
	Clock clock;
	srand(std::time(0));
	auto life = new GameObject("Player.png");
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
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		for (int i = 0; i < gameObjects.size(); i++) {
			window.draw(gameObjects[i]->sprite);
		}
		for (int i = 0; i < playerLives; i++) {
			life->sprite.setPosition(WindowWidth - 300 + 75 * i, 0);
			window.draw(life->sprite);
		}
		window.display();
		if (exit) window.close();
	}
}

void Game::Exit()
{
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
