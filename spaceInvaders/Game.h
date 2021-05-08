#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
class Fire;
class Timer;
using namespace std;
using namespace sf;

enum Type { player, fire, enemy, wall };

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
public:
	float time;
	static Game* Instance;
	vector<GameObject*> gameObjects;
	vector<Timer*> timers;
	int WindowWidth = 1000;
	int WindowHeight = 650;
	Game();
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
	Timer* shootTimer = new Timer(0.5);
	float speed = 0.2f;
public:
	Player(int startX, int startY);
	~Player();
	virtual void Update() override;
	virtual void Interspect(GameObject* obj) override;
};

class Enemy : public GameObject {
private:
	Timer* moveTimer = new Timer(0.25);
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
	Fire(int startX, int startY, float speed, int dir);
	virtual void Update() override;
	virtual void Interspect(GameObject* obj) override;
};

class Wall : public GameObject {
public:
	Wall(int startX, int startY);
	virtual void Interspect(GameObject* obj) override;
};

#endif
