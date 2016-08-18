#include "Window.h"
#include <SFML/Window/Event.hpp>
#include <gl/glew.h>
#include <iostream>

de::Window::Window() : _window(sf::VideoMode(900,800), "Distend Engine", sf::Style::Default, sf::ContextSettings(24,8,8,4,5))
{
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cout << "Glew could not be started" << std::endl;
	}
	glClearColor(0.2f, 0.5f, 0.9f, 1.0f);
}


de::Window::~Window()
{
	_window.close();
}

void de::Window::setSize(const glm::ivec2& windowSize)
{
	_window.setSize(sf::Vector2u(windowSize.x, windowSize.y));
}

void de::Window::setSize(const int& winX, const int& winY)
{
	_window.setSize(sf::Vector2u(winX, winY));
}

void de::Window::setSize(const sf::Vector2u& windowSize)
{
	_window.setSize(windowSize);
}

void de::Window::setClearColor(const sf::Color& color)
{
	glClearColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255);
}

void de::Window::setClearColor(const glm::vec4& color)
{
	glClearColor(color.x, color.y, color.z, color.w);
}

void de::Window::pollEvents()
{
	sf::Event event;
	while(_window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
		{
			_window.close();
		}
		if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::Escape)
			{
				_window.close();
			}
		}
	}
}

void de::Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void de::Window::display()
{
	_window.display();
}
