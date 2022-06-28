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

class FontSheet {
private:
    nlohmann::json my_FontData;
    sf::Font my_font;
public:
    FontSheet(std::string filepath);

    sf::Font getFont();
    //sf::Vector2u getTextSizing();
};


class GUI_TextureHolder
{
private:
    SpriteSheet* my_mapSpritesheet;
    SpriteSheet* my_playerSpritesheet;
    SpriteSheet* my_enemySpritesheet;
    SpriteSheet* my_chestSpritesheet;
    SpriteSheet* my_itemSpritesheet;

    FontSheet* my_CMDFontSheet;

public:
    GUI_TextureHolder();

    SpriteSheet* get_MapSprites();
    SpriteSheet* get_PlayerSprites();
    SpriteSheet* get_EnemySprites();
    SpriteSheet* get_ChestSprites();

    SpriteSheet* get_ItemSprites();

    FontSheet* get_CMDFontSheet();

    ~GUI_TextureHolder();
};

