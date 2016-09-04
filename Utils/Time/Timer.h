#pragma once
#include <SFML/System/Clock.hpp>
class Timer
{
public:
	void start();
	void update();
	bool shouldUpdate();
	void refreshTime();
	float getFPS();
private:
	sf::Clock _clock;
	sf::Time _totalTime, _deltaTime, _currentTime, _accumulator, _newTime, _frameTime;
	int _frames;
};