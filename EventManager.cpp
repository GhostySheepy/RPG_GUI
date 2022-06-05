#include "EventManager.h"
#include <iostream>

KeyBind::KeyBind()
{
	my_triggerOnNextReq = false;
	my_unpressed = true;
	my_triggerDelay = SETTINGS.Input_Cutoff;
}

KeyBind::~KeyBind()
{
}

void KeyBind::KeyPressed()
{
	if (my_unpressed == true) {
		std::cout << "Bind:KeyPressed" << std::endl;
		my_triggerOnNextReq = true;
		my_unpressed = false;
	}
}

void KeyBind::KeyReleased()
{
	my_unpressed = true;
}

bool KeyBind::GetKeyTriggerState()
{
	if (my_triggerOnNextReq == true) {
		my_triggerOnNextReq = false;
		return true;
	}
	else {
		
		return false;
	}

}

EventManager::EventManager()
{
	my_keyBinds = {};
}

EventManager::~EventManager()
{
}

void EventManager::Handle(sf::Event event)
{
	auto found = my_keyBinds.find(event.key.code);
	if (event.type == sf::Event::KeyPressed && found == my_keyBinds.end()) {
		std::cout << "wrong one" << std::endl;
	}
	if (event.type == sf::Event::KeyPressed && found != my_keyBinds.end()) {
		found->second.KeyPressed();
		
	}
	else if (event.type == sf::Event::KeyReleased && found != my_keyBinds.end()) {
		found->second.KeyReleased();
	}

}

std::vector<bool> EventManager::AskForTriggers(std::vector<sf::Keyboard::Key> askedTriggers)
{
	std::vector<bool> answer = {};
	for (auto key : askedTriggers) {
		if (my_keyBinds.find(key) == my_keyBinds.end()) {
			my_keyBinds.insert({ key, KeyBind() });
		}
		answer.push_back(my_keyBinds.find(key)->second.GetKeyTriggerState());
		
	}
	return answer;
}

