#include "Window.h"

#include "GL/glew.h"
#include <SFML/Window/Mouse.hpp>
#include <iostream>

// create a window
void Window::createWindow(const int& width, const int& height, const std::string& title, const unsigned& style, const sf::ContextSettings& settings)
{
	_window.create(sf::VideoMode(width, height), title, style, settings);
	_window.setFramerateLimit(60);
	_window.setMouseCursorVisible(false);
	createGLContext();
}

// returns true if the window is still open
bool Window::isOpen() const
{
	return _window.isOpen();
}

// sets the icon of our window ( at the top )
void Window::setWindowIcon(const std::string& iconPath)
{
	sf::Image image;
	image.loadFromFile(iconPath);
	_window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}

void Window::centerMouse()
{
	sf::Mouse::setPosition(sf::Vector2i(_window.getSize().x / 2, _window.getSize().y / 2) ,_window);
}


// clears using openGL clear
void Window::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// displays using a double buffer
void Window::display()
{
	_window.display();
}

// closes the window
void Window::close()
{
	_window.close();
}

// setups up our window with glew
void Window::createGLContext() const
{
	auto error = glewInit();

	if(error != GLEW_OK)
	{
		std::cout << "OpenGL could not be created" << std::endl;
	}
	else
	{
		glewExperimental = GL_TRUE;
	}
}

glm::ivec2 Window::getSize()
{
	auto windowSize = _window.getSize();
	return glm::ivec2(windowSize.x, windowSize.y);
}

glm::ivec2 Window::getMousePos()
{
	auto mousePos = sf::Mouse::getPosition(_window);
	return glm::ivec2(mousePos.x, mousePos.y);
}

bool Window::pollEvents(sf::Event& event)
{
	return _window.pollEvent(event);
}
