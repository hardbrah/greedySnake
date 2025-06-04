// Settings.h
#pragma once
#include <SFML/Graphics.hpp>

namespace sfSnake
{
    struct Settings
    {
        sf::Color backgroundColor = sf::Color::Black;
        sf::Color gridColor = sf::Color::White;
        bool showGrid = false;

        static Settings &getInstance(); // 单例
    };
}
