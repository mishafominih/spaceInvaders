#include "Game.h"
#include <iostream>

using namespace std;


Timer::Timer(float time) {
	index = Game::Instance->timers.size();
	timer = 0;
	this->time = time;
	Game::Instance->timers.push_back(this);
}

void Timer::Tick(float time) {
	timer += time;
}

bool Timer::IsTime() {
	return timer >= time;
}

void Timer::Restart() {
	timer = 0;
}