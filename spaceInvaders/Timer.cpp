#include "Game.h"


Timer::Timer(float time) {
	timer = 0;
	this->time = time;
	Game::Instance->timers.push_back(this);
	index = Game::Instance->timers.size();
}

void Timer::Tick() {
	float time = Game::Instance->clock.getElapsedTime().asMicroseconds();
	time = time / 500;
	timer += time;
}

bool Timer::IsTime() {
	return timer >= time;
}

void Timer::Restart() {
	timer = 0;
}

void Timer::Del() {
	auto iter = Game::Instance->timers.cbegin(); // указатель на первый элемент
	Game::Instance->timers.erase(iter + index);   // удаляем третий элемент
	delete this;
}