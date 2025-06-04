// SettingsScreen.h
#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"

namespace sfSnake
{
    class SettingsScreen : public Screen
    {
    public:
        SettingsScreen();
        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;

    private:
        sf::Font font_;
        sf::Text text_;
        sf::Sprite backgroundSprite_;
    };
}
