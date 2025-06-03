#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_()
{
	fruitCount_ = {1, 2, 2, 2, 1};

	// Load background texture
	if (!backgroundTexture_.loadFromFile("Images/background.png"))
	{
		// If loading fails, create a default colored background
		backgroundSprite_.setTextureRect(sf::IntRect(0, 0, Game::Width, Game::Height));
		backgroundSprite_.setColor(sf::Color(50, 50, 50)); // Dark gray background
	}
	else
	{
		backgroundSprite_.setTexture(backgroundTexture_);
		// Scale to fit window
		float scaleX = static_cast<float>(Game::Width) / backgroundTexture_.getSize().x;
		float scaleY = static_cast<float>(Game::Height) / backgroundTexture_.getSize().y;
		backgroundSprite_.setScale(scaleX, scaleY);
	}
}

void GameScreen::handleInput(sf::RenderWindow &window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	generateFruit(); // auto generate fruit if needed

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_, fruitCount_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow &window)
{
	window.draw(backgroundSprite_);

	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
}
void GameScreen::generateFruit()
{
	while (fruitCount_.black > 0)
	{
		generateFruit_(FruitType::Black);
		fruitCount_.black--;
	}
	while (fruitCount_.blue > 0)
	{
		generateFruit_(FruitType::Blue);
		fruitCount_.blue--;
	}
	while (fruitCount_.green > 0)
	{
		generateFruit_(FruitType::Green);
		fruitCount_.green--;
	}
	while (fruitCount_.red > 0)
	{
		generateFruit_(FruitType::Red);
		fruitCount_.red--;
	}
	while (fruitCount_.brown > 0)
	{
		generateFruit_(FruitType::Brown);
		fruitCount_.brown--;
	}
}
void GameScreen::generateFruit_(FruitType type)
{
	static std::default_random_engine engine(std::random_device{}());
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);

	fruit_.push_back(FruitFactory::createFruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), type));
}
