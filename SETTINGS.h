#pragma once
constexpr auto SAVES_FOLD = "Saves//";
constexpr auto ITEMS_LOC = "Data//Items.json";
constexpr auto DEF_SAVE = "Data//Zero_save.json";

constexpr auto ENEMY_TEX = "Data//Pictures//Enemy.json";
constexpr auto PLAYER_TEX = "Data//Pictures//Player.json";
constexpr auto MAP_TEX = "Data//Pictures//Map.json";

#include <SFML/Window.hpp>

class Settings
{
public:
    static Settings& Instance()
    {
        static Settings stgs;
        return stgs;
    }

public:

    int Framerate = 30;
    int Input_Cutoff = Framerate;


    sf::Keyboard::Key Key_TooggleFullscreen = sf::Keyboard::F5;

    sf::Keyboard::Key Key_WalkForward = sf::Keyboard::W;
    sf::Keyboard::Key Key_WalkBacward = sf::Keyboard::S;
    sf::Keyboard::Key Key_WalkLeft = sf::Keyboard::A;
    sf::Keyboard::Key Key_WalkRight = sf::Keyboard::D;


    sf::Vector2f window_dot0 = { 0.8, 0.8 };



};

namespace {

    Settings& SETTINGS = Settings::Instance();
}

