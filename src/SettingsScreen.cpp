// SettingsScreen.cpp
#include "SettingsScreen.h"
#include "MenuScreen.h"
#include "Settings.h"
#include "Game.h"

using namespace sfSnake;

SettingsScreen::SettingsScreen()
{
    font_.loadFromFile("Fonts/game_over.ttf");
    text_.setFont(font_);
    text_.setCharacterSize(24);
    text_.setFillColor(sf::Color::Green);
    text_.setString(
        "Settings:\n\n"
        "[1] Black background\n"
        "[2] White background\n"
        "[3] Brown background\n"
        "[4] Grid Color: Black\n"
        "[5] Grid Color: White\n"
        "[6] Grid Color: Brown\n"
        "[G] Toggle Grid On/Off\n\n"
        "[ESC] Back to Menu");

    text_.setPosition(50, 50);
}

void SettingsScreen::handleInput(sf::RenderWindow &window)
{
    auto &settings = Settings::getInstance();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        settings.backgroundColor = sf::Color::Black;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        settings.backgroundColor = sf::Color::White;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        settings.backgroundColor = sf::Color(153, 51, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        settings.gridColor = sf::Color::Black;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        settings.gridColor = sf::Color::White;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        settings.gridColor = sf::Color(153, 51, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
        settings.showGrid = !settings.showGrid;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        Game::Screen = std::make_shared<MenuScreen>();
}

void SettingsScreen::update(sf::Time) {}

void SettingsScreen::render(sf::RenderWindow &window)
{
    auto &settings = Settings::getInstance();
    window.clear(settings.backgroundColor);
    backgroundSprite_.setTextureRect(sf::IntRect(0, 0, Game::Width, Game::Height));
    window.draw(backgroundSprite_);
    if (settings.showGrid)
    {
        const int gridSize = 20;
        sf::VertexArray gridLines(sf::Lines);
        for (int x = 0; x <= Game::Width; x += gridSize)
        {
            gridLines.append(sf::Vertex(sf::Vector2f(x, 0), settings.gridColor));
            gridLines.append(sf::Vertex(sf::Vector2f(x, Game::Height), settings.gridColor));
        }
        for (int y = 0; y <= Game::Height; y += gridSize)
        {
            gridLines.append(sf::Vertex(sf::Vector2f(0, y), settings.gridColor));
            gridLines.append(sf::Vertex(sf::Vector2f(Game::Width, y), settings.gridColor));
        }
        window.draw(gridLines);
    }
    window.draw(text_);
}
