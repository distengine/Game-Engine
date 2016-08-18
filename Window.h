#pragma once
// Distend Engine namespace Window Class
// This Class handles the cross platform window creation process
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace de {
	class Window
	{
	public:
		// This will create a window with 900x800, "Distend Enginge", and default window / 4.5 openGL context settings
		Window();
		// This will destroy the window
		~Window();
		// We won't initialize all the setters/getters are the moment, only the ones we need

		void setSize(const glm::ivec2& windowSize);
		void setSize(const int& winX, const int& winY);
		void setSize(const sf::Vector2u& windowSize);

		void setClearColor(const sf::Color& color);
		void setClearColor(const glm::vec4& color);

		const glm::ivec2& glmGetSize() const
		{
			return glm::ivec2(_window.getSize().x, _window.getSize().y);
		}
		const sf::Vector2u& sfGetSize() const
		{
			return _window.getSize();
		}
		
		// This will poll all window/mouse/keyboard events
		void pollEvents();
		// calls our clear buffer bits
		void clear();
		// Displays the window to the screen
		void display();
		// Returns the current window state
		bool isOpen() const
		{
			return _window.isOpen();
		}
	private:
		sf::RenderWindow _window;
	};
}