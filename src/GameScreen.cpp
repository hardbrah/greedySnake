#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "Settings.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_()
{
	fruitCount_ = {1, 2, 2, 2, 1};
	backgroundSprite_.setTextureRect(sf::IntRect(0, 0, Game::Width, Game::Height));
	auto &settings = Settings::getInstance();
	backgroundSprite_.setColor(settings.backgroundColor);
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
	auto &settings = Settings::getInstance();
	window.clear(settings.backgroundColor);
	window.draw(backgroundSprite_);
	if (settings.showGrid)
	{ // 绘制网格
		sf::VertexArray gridLines(sf::Lines);
		const int gridSize = 20;
		// 绘制垂直线
		for (int x = 0; x <= Game::Width; x += gridSize)
		{
			gridLines.append(sf::Vertex(sf::Vector2f(x, 0), settings.gridColor));
			gridLines.append(sf::Vertex(sf::Vector2f(x, Game::Height), settings.gridColor));
		}

		// 绘制水平线
		for (int y = 0; y <= Game::Height; y += gridSize)
		{
			gridLines.append(sf::Vertex(sf::Vector2f(0, y), settings.gridColor));
			gridLines.append(sf::Vertex(sf::Vector2f(Game::Width, y), settings.gridColor));
		}

		window.draw(gridLines);
	}
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
