#include "pch.h"
#include "CppUnitTest.h"
#include "../spaceInvaders/Game.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Function
{
	class FakeGame : public Game {
	public:
		Clock clock;
		FakeGame(int countIteration) {
			Instance = this;
		}
		void Update() {
			time = clock.getElapsedTime().asSeconds();
			clock.restart();
			for (int i = 0; i < timers.size(); i++) {//итерация таймеров
				timers[i]->Tick(time);
			}

			for (int i = 0; i < gameObjects.size(); i++) {//обновление состояний игровых объектов
				gameObjects[i]->Update();
			}

			CheckInterspect();

		}
	};

	TEST_CLASS(Function)
	{
	public:
		TEST_METHOD(endGame)
		{
			auto g = new Game(4, true);
			Assert::IsTrue(Game::result == Result::exite);
		}
		TEST_METHOD(DieEnemy)
		{
			auto game = new FakeGame(100);
			auto enemy = new Enemy(100, 100);
			auto fire = new Fire(100, 100, 1, 1, playerfire);
			game->AddGameObject(enemy);
			game->AddGameObject(fire);
			enemy->Interspect(fire);
			Assert::IsTrue(game->gameObjects.size() == 0);
		}
		TEST_METHOD(moveLeftAI)
		{
			auto game = new FakeGame(100);
			auto AI = new Computer(100, 300);
			game->AddGameObject(AI);
			AI->left();
			Assert::IsTrue(AI->x < 100);
		}
		TEST_METHOD(moveRightAI)
		{
			auto game = new FakeGame(100);
			auto AI = new Computer(100, 300);
			game->AddGameObject(AI);
			AI->right();
			Assert::IsTrue(AI->x > 100);
		}
		TEST_METHOD(shootAI)
		{
			auto game = new FakeGame(100);
			auto AI = new Computer(100, 300);
			game->AddGameObject(AI);
			AI->fire();
			Assert::IsTrue(game->gameObjects.size() == 2);
		}
	};
}
