#pragma once
#include <SFML/Window.hpp>
#include <vector>
#include <unordered_map>
#include "SETTINGS.h"

#include <stdio.h>

class KeyBind {
public:
	KeyBind();
	~KeyBind();

	void KeyPressed();
	void KeyReleased();
	bool GetKeyTriggerState();

private:
	bool my_unpressed;
	bool my_triggerOnNextReq;
	int my_triggerDelay;
};
class EventManager
{
public:
	EventManager();
	~EventManager();

	void Handle(sf::Event event);
	std::vector<bool> AskForTriggers(std::vector<sf::Keyboard::Key> askedTriggers);
private:
	std::unordered_map< sf::Keyboard::Key, KeyBind > my_keyBinds;
};

