#include "Game.h"
#include <GL/glew.h>
#include <SFML/Window/Event.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>


void Game::start()
{
	loadSubsytems();
	loadGLSettings();
	gameLoop();

}

void Game::loadSubsytems()
{
	_window.createWindow(1920, 1080, "Distend", sf::Style::Default, sf::ContextSettings(24, 8, 8, 4, 5));

	_camera.setPosition(glm::vec3(0.0f, 0.0f, -10.0f));
	_camera.setLookAt(glm::vec3(0.0f, 1.0f, 0.0f));
	_camera.setViewport(0, 0, _window.getSize().x, _window.getSize().y);
}

void Game::loadGLSettings()
{
	glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.2f, 0.5f, 0.6f, 1.0f);
	_sky.setupSkyBox(std::vector<std::string>{
		"Textures/Skybox/SkyNight/right-sky-night.png",
			"Textures/Skybox/SkyNight/left-sky-night.png",
			"Textures/Skybox/SkyNight/top-sky-night.png",
			"Textures/Skybox/SkyNight/bot-sky-night.png",
			"Textures/Skybox/SkyNight/front-sky-night.png",
			"Textures/Skybox/SkyNight/back-sky-night.png"
	});
	_cube.create(glm::vec3(2), glm::vec3(3), std::vector<std::string>{"Textures/wall.png"});
	_cube2.create(glm::vec3(5), glm::vec3(2), glm::vec3(0.5, 0.3, 0.4));
}

void Game::gameLoop()
{
	sf::Clock clock;
	clock.restart();
	while (_window.isOpen())
	{
		processInput();
		if (_paused != true)
		{
			update(clock.getElapsedTime().asSeconds());
			render();
		}
		clock.restart();
	}
}

void Game::update(float dt)
{
	_camera.moveKeyboard();
	_camera.update();
	_camera.processMouseButtons();
	_camera.processMouseMovement(_window);

	glm::mat4 view, projection;

	_camera.getMatrices(view, projection);

	_sky.update(view, projection);
	_cube.update(view, projection);
	_cube2.update(view, projection);
}

void Game::processInput()
{
	sf::Event event;
	while(_window.pollEvents(event))
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
			if(event.key.code == sf::Keyboard::Add)
			{
				_cube.move(glm::vec3(0.0f, 0.0f, 1.0f));
			}
			if (event.key.code == sf::Keyboard::Subtract)
			{
				_cube.move(glm::vec3(0.0f, 0.0f, -1.0f));
			}
		}
		if(event.type == sf::Event::GainedFocus)
		{
			_paused = false;
		}
		if (event.type == sf::Event::LostFocus)
		{
			_paused = true;
		}
	}
}

void Game::render()
{
	_window.clear();

	_cube.render();
	_cube2.render();

	_sky.renderSkyBox();

	_window.display();
}