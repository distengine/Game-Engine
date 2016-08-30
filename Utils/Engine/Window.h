#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <glm/detail/type_vec2.hpp>

class Window
{
public:
	// Create a window 
	// Size 1 - 2
	// Title 3
	// Window Style 4 - FullScreen, Default, Borderless
	// Settings 5 - For OpenGL and depth/stencil settings + AA
	void createWindow(const int& width, const int& height,
		const std::string& title, const unsigned& style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
	// Check if the window is still open
	bool isOpen() const;
	// Checks if the window is active
	bool isActive() const;
	// Check to see if our event queue has any events left to poll
	bool pollEvents(sf::Event& event);
	// Returns a glm::ivec2 of the size
	glm::ivec2 getSize();
	// Returns the position of the mouse
	glm::ivec2 getMousePos();
	// Set window icon
	void setWindowIcon(const std::string& iconPath);
	// Sets the mouse position
	void centerMouse();
	// Clears the window with openGL
	void clear() const;
	// Displays the window
	void display();
	// Closes the window
	void close();

private:
	// Setup our OpenGL settings
	void createGLContext() const;

	sf::RenderWindow _window;
};
