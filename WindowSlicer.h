#pragma once



#include <SFML/Graphics.hpp>
#include "SETTINGS.h"
#include "Window.h"

namespace WindowSlicer {
	inline sf::View getMapWiev(Window* current_window) {
		sf::Vector2u currentWindowSize = current_window->GetWindowSize();

		sf::Vector2u mapWindow_size = { 
			static_cast<unsigned int>(currentWindowSize.x * SETTINGS.window_dot0.x), 
			static_cast<unsigned  int>(currentWindowSize.y * SETTINGS.window_dot0.y) 
		};

		sf::View resulting_View(sf::FloatRect(0, 0, mapWindow_size.x, mapWindow_size.y));
		resulting_View.setViewport(sf::FloatRect(0, 0, SETTINGS.window_dot0.x, SETTINGS.window_dot0.y));
		return resulting_View;
	};

	inline sf::View getInventoryView(Window* current_window) {
		sf::Vector2u currentWindowSize = current_window->GetWindowSize();

		sf::Vector2u invWindow_size = { 
			static_cast<unsigned int>(currentWindowSize.x * (1 - SETTINGS.window_dot0.x)), 
			static_cast<unsigned  int>(currentWindowSize.y)
		};

		sf::View resulting_View(sf::FloatRect(
			0, 
			0, 
			invWindow_size.x, 
			invWindow_size.y
		));

		resulting_View.setViewport(sf::FloatRect(
			SETTINGS.window_dot0.x,
			0, 
			1 - SETTINGS.window_dot0.x, 
			1
		));
		return resulting_View;
		 
	}

	inline sf::View getCMDView(Window* current_window) {
		sf::Vector2u currentWindowSize = current_window->GetWindowSize();

		sf::Vector2u cmdWindow_size = {
			static_cast<unsigned int>(currentWindowSize.x * SETTINGS.window_dot0.x),
			static_cast<unsigned  int>(currentWindowSize.y * (1 - SETTINGS.window_dot0.y))
		};

		sf::View resulting_View(sf::FloatRect(
			0,
			0,
			cmdWindow_size.x,
			cmdWindow_size.y
		));

		resulting_View.setViewport(sf::FloatRect(
			0,
			SETTINGS.window_dot0.y,
			SETTINGS.window_dot0.x,
			1 - SETTINGS.window_dot0.y
		));
		return resulting_View;
	}
}

