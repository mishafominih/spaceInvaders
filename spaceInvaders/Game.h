#ifndef GAME_H
#define GAME_H

#include "pch.h"
#include <SFML/Graphics.hpp>
#include <vector>
namespace Function {
	class Fire;
	class Timer;
	using namespace std;
	using namespace sf;

	enum Type { player, playerfire, enemyFire, enemy, wall, nothing };
	enum Result { win, lose, exite };

	class GameObject {
	public:
		Type type;
		int index;
		Image image;
		Texture texture;
		Sprite sprite;
		float x;
		float y;
		GameObject(String imagePath);
		virtual ~GameObject();
		virtual void Update() { }
		virtual void Interspect(GameObject* obj) { }
	};

	class Game {
	protected:
		void CreateEnemy();
		void CheckInterspect();
		void CreateWall();
		void SetPlayer(bool isPlayer);
		Game();
		bool exit = false;
	public:
		static Result result;
		float time;
		float speedShoot;
		static Game* Instance;
		vector<GameObject*> gameObjects;
		vector<Timer*> timers;
		int WindowWidth = 1000;
		int WindowHeight = 650;
		Game(float speedShoot, bool isPlayer);
		void CheckBots();
		int playerLives = 3;
		void Exit(Result res);
		void AddGameObject(GameObject* obj);
		void DelGameObject(GameObject* obj);
		void AddTimer(Timer* timer);
		void DelTimer(Timer* timer);
	};

	class Timer
	{
		float time;
		float timer;
	public:
		float index;
		Timer(float time);
		void Tick(float time);
		bool IsTime();
		void Restart();
	};

	class Player : public GameObject {
	protected:
		Timer* shootTimer = new Timer(0.25);
		float speed = 0.15f;
	public:
		Player(int startX, int startY);
		~Player();
		virtual void Update() override;
		virtual void Interspect(GameObject* obj) override;
	};

	class Enemy : public GameObject {
	private:
		Timer* moveTimer = new Timer(0.05);
		Timer* shootTimer;
		int radius = 100;
		float speed = 0.6;
		bool right = true;
		int startX;
	public:
		Enemy(int startX, int startY);
		~Enemy();
		virtual void Update() override;
		virtual void Interspect(GameObject* obj) override;
	};

	class Fire : public GameObject {
	private:
		float speed = 0.2f;
		int dir;
	public:
		Fire(int startX, int startY, float speed, int dir, Type type);
		virtual void Update() override;
		virtual void Interspect(GameObject* obj) override;
	};

	class Wall : public GameObject {
	public:
		Wall(int startX, int startY);
		virtual void Interspect(GameObject* obj) override;
	};

	class Computer : public Player {
	private:
		bool isFireOnLine(float first, float second);
	public:
		Computer(int startX, int startY);
		virtual void Update() override;
		void movePlayer();
		void fire();
		void right();
		void left();
	};
}
#endif
