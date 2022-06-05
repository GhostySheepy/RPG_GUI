#include "GUI_TextureHolder.h"


SpriteSheet::SpriteSheet(std::string filepath)
{
    std::ifstream sprite_file(filepath);
    sprite_file >> spritesData;
    sprite_file.close();

    sf::Image new_image;
    new_image.loadFromFile(spritesData["img_file"]);
    my_spriteSheet.loadFromImage(new_image);
}

sf::Sprite SpriteSheet::getSpriteFor(int sprite_specifier)
{
    int max_specifier = spritesData["max_count"];
    sf::Sprite new_sprite;
    
    if (sprite_specifier < max_specifier && sprite_specifier >= 0) {

        my_spriteSheet.setSmooth(spritesData["spriteData"]["set_smooth"][sprite_specifier]);
        new_sprite.setTexture(my_spriteSheet);
        new_sprite.setTextureRect({
            spritesData["spriteData"]["framing"][sprite_specifier][0],
            spritesData["spriteData"]["framing"][sprite_specifier][1],
            spritesData["spriteData"]["sizing"][0],
            spritesData["spriteData"]["sizing"][1]
            });
        sf::Color new_sprite_color(
            spritesData["spriteData"]["set_color"][sprite_specifier][0],
            spritesData["spriteData"]["set_color"][sprite_specifier][1],
            spritesData["spriteData"]["set_color"][sprite_specifier][2],
            spritesData["spriteData"]["set_color"][sprite_specifier][3]
        );
        new_sprite.setColor(new_sprite_color);
    }
    else {
        new_sprite.setTexture(my_spriteSheet);
        my_spriteSheet.setSmooth(spritesData["spriteData"]["set_smooth"][max_specifier]);
        new_sprite.setTextureRect({
            spritesData["spriteData"]["framing"][max_specifier][0],
            spritesData["spriteData"]["framing"][max_specifier][1],
            spritesData["spriteData"]["sizing"][0],
            spritesData["spriteData"]["sizing"][1]
            });
    }
    return new_sprite;
}

sf::Vector2u SpriteSheet::getSpriteSizing()
{
    return {spritesData["spriteData"]["sizing"][0], spritesData["spriteData"]["sizing"][1]};
}

GUI_TextureHolder::GUI_TextureHolder()
{
    my_mapSpritesheet = new SpriteSheet(MAP_TEX);
    my_playerSpritesheet = new SpriteSheet(PLAYER_TEX);
    my_enemySpritesheet = new SpriteSheet(ENEMY_TEX);
}

SpriteSheet* GUI_TextureHolder::get_MapSprites()
{
    return my_mapSpritesheet;
}

SpriteSheet* GUI_TextureHolder::get_PlayerSprites()
{
    return my_playerSpritesheet;
}

SpriteSheet* GUI_TextureHolder::get_EnemySprites()
{
    return my_enemySpritesheet;
}

GUI_TextureHolder::~GUI_TextureHolder()
{
    delete my_mapSpritesheet;
}
