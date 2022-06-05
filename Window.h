#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "EventManager.h"

#include "SETTINGS.h"

class Window
{
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void BeginDraw();

	void SetView(sf::View new_view);
	sf::View GetDefaultView();

	void Draw(sf::Drawable const &drawable);
	void EndDraw();

	void Update();

	bool IsDone();
	bool IsFullscreen();
	bool IsFocused();

	void ToggleFullscreen();
	void Close();

	EventManager* GetEventManager();
	sf::Vector2u GetWindowSize();

private:
	void Setup(const std::string& title, const sf::Vector2u& size);
	void Create();

	sf::RenderWindow my_window;
	EventManager my_eventManager;
	sf::Vector2u my_windowSize;
	std::string my_windowTitle;

	bool my_isDone;
	bool my_isFullscreen;
	bool my_isFocused;
};

