#include "Window.h"
#include "SETTINGS.h"
#include <iostream>

Window::Window()
{
	Setup("DA GAME", sf::Vector2u(960, 540));
}

Window::Window(const std::string& title, const sf::Vector2u& size)
{
	Setup(title, size);
}

Window::~Window() 
{
	my_window.close(); 
}

void Window::BeginDraw()
{
	my_window.clear(sf::Color::Black);
}

void Window::SetView(sf::View new_view)
{
	my_window.setView(new_view);
}
sf::View Window::GetDefaultView()
{
	return my_window.getDefaultView();
}

void Window::Draw(sf::Drawable const &drawable)
{
	my_window.draw(drawable);
}

void Window::EndDraw() 
{ 
	my_window.display(); 
}

void Window::Update()
{
	sf::Event event;
	while (my_window.pollEvent(event)) {

		switch (event.type) {
		case sf::Event::Closed:
			std::cout << "done" << std::endl;
			my_isDone = true;
			break;
		case sf::Event::Resized:
			my_windowSize = { event.size.width, event.size.height };
			break;


		case sf::Event::KeyPressed:
			if (event.key.code == SETTINGS.Key_TooggleFullscreen) {
				ToggleFullscreen();
				break;
			}
		default:
			my_eventManager.Handle(event);
		}
	}
}

bool Window::IsDone() 
{ 
	return my_isDone; 
}
bool Window::IsFullscreen() 
{ 
	return my_isFullscreen; 
}
bool Window::IsFocused() 
{ 
	return my_isFocused; 
}

void Window::ToggleFullscreen()
{
	my_isFullscreen = !my_isFullscreen;
	Close();
	Create();
}

void Window::Close()
{
	my_isDone = true;
	my_window.close();
}

EventManager* Window::GetEventManager()
{
	return &my_eventManager;
}

sf::Vector2u Window::GetWindowSize()
{
	return my_window.getSize();
}

void Window::Setup(const std::string& title, const sf::Vector2u& size) {
	my_windowTitle = title;
	my_windowSize = size;
	my_isFullscreen = false;
	my_isFocused = true;

	my_eventManager = EventManager();

	Create();
}

void Window::Create()
{
	my_isDone = false;
	sf::Uint32 style = sf::Style::Default;
	if (my_isFullscreen) { style = sf::Style::Fullscreen; }

	my_window.create(sf::VideoMode(my_windowSize.x, my_windowSize.y, 32), my_windowTitle, style);
}

sf::RenderWindow& Window::getRenderWindow()
{
	return my_window;
}