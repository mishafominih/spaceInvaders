#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
class Fire;
class Timer;
using namespace std;
using namespace sf;

enum Type { player, playerfire, enemyFire, enemy, wall, nothing};

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
private:
	void CreateEnemy();
	void CheckInterspect();
	bool exit = false;
public:
	float time;
	static Game* Instance;
	vector<GameObject*> gameObjects;
	vector<Timer*> timers;
	int WindowWidth = 1000;
	int WindowHeight = 650;
	Game();
	int playerLives = 3;
	void Exit();
	void CreateWall();
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
private:
	Timer* shootTimer = new Timer(0.25);
	float speed = 0.2f;
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
	float speed = 1;
	bool right = true;
	int realX;
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

#endif
