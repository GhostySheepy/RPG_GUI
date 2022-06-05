#include <iostream>
#include <cstdlib>
#include <ctime>

#include <iomanip>


/*#include "Player.h"
#include "Enemy.h"
#include "NotEnemy.h"
#include "Item.h"
#include "Chest.h"*/
#include "Manager.h"

#include "Window.h"
#include "SFML/Graphics.hpp"
#include "SETTINGS.h"

#include "GUI_TextureHolder.h"


//#include "Custom_Init.h"

/*int main()
{
	//srand(static_cast<unsigned int>(time(NULL)));
	//npc::Director director;
	//std::vector<std::shared_ptr<npc::Enemy>> enemyList;
	//npc::createEnemy(director, enemyList, { "A", 4 });
	
	Manager test_manager;

	test_manager.startNewGame();

	test_manager.GameLoop();

}*/

#include <SFML/Graphics.hpp>

void main() {
    Manager new_manager;
    new_manager.startNewGame();
    new_manager.GameLoop();
    
}

const sf::Vector2f leftSize(1440.0f, 1080.0f);
const sf::Vector2f rightSize(480.0f, 1080.0f);
const sf::Vector2f origin(0.0f, 0.0f);



void mainn()
{
    GUI_TextureHolder new_holder;

    sf::Sprite new_sprite = new_holder.get_MapSprites()->getSpriteFor(3);
    new_sprite.setPosition(0, 0);
    sf::RenderWindow window(sf::VideoMode(640, 480), "Text & View");

    sf::View view(sf::FloatRect(origin, leftSize));
    view.zoom(0.5);
    view.setCenter(0, 0);

    sf::Image img;
    img.loadFromFile("tilesheet.png");

    sf::Texture texture;
    texture.create(200, 200);

    texture.update(img);
    texture.setRepeated(true);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    
    sprite.setPosition(0, 0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.setView(view);
        window.draw(new_sprite);

        //window.setView(rightView);
        //window.draw(rect);
        //window.draw(text);

        window.display();
    }
}