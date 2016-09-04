#include "Timer.h"
#include <iostream>
#include <SFML/System/Sleep.hpp>

void Timer::start()
{
	_clock.restart();
	_deltaTime = sf::Time(sf::seconds(0.01));
	_currentTime = _clock.getElapsedTime();
}

void Timer::update()
{
	_frames++;
	_newTime = _clock.getElapsedTime();
	_frameTime = _newTime - _currentTime;
	_currentTime = _newTime;

	_accumulator += _frameTime;
}

bool Timer::shouldUpdate()
{
	if (_accumulator >= _deltaTime)
	{
		refreshTime();
		return true;
	}
	else
	{
		return false;
	}
}

void Timer::refreshTime()
{
	_accumulator -= _deltaTime;
	_totalTime += _deltaTime;
}

float Timer::getFPS()
{
	return _frameTime.asSeconds();
}