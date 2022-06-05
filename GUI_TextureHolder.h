#pragma once


#include "SETTINGS.h"

#include<SFML/Graphics.hpp>
#include "Include/json.hpp"
#include <iostream>
#include <iomanip>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>


class SpriteSheet {
private:
    nlohmann::json spritesData;
    sf::Texture my_spriteSheet;
public:
    SpriteSheet(std::string filepath);

    sf::Sprite getSpriteFor(int sprite_specifier);
    sf::Vector2u getSpriteSizing();
};


class GUI_TextureHolder
{
private:
    SpriteSheet* my_mapSpritesheet;
    SpriteSheet* my_playerSpritesheet;
    SpriteSheet* my_enemySpritesheet;

public:
    GUI_TextureHolder();

    SpriteSheet* get_MapSprites();
    SpriteSheet* get_PlayerSprites();
    SpriteSheet* get_EnemySprites();

    ~GUI_TextureHolder();
};

