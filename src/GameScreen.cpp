#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "Settings.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

const float GameScreen::MinDistanceFromSpawn = 100.0f;

GameScreen::GameScreen() : snake_()
{
	fruitCount_ = {1, 2, 2, 2, 1};
	backgroundSprite_.setTextureRect(sf::IntRect(0, 0, Game::Width, Game::Height));
	auto &settings = Settings::getInstance();
	backgroundSprite_.setColor(settings.backgroundColor);

	// 生成障碍物
	generateObstacles();
}

void GameScreen::generateObstacles()
{
	static std::default_random_engine engine(std::random_device{}());
	static std::uniform_int_distribution<int> xDistribution(20, Game::Width - 60);
	static std::uniform_int_distribution<int> yDistribution(20, Game::Height - 60);

	sf::Vector2f spawnPoint(Game::Width / 2, Game::Height / 2); // 蛇的出生点

	for (int i = 0; i < ObstacleCount; ++i)
	{
		sf::Vector2f obstaclePos;
		bool validPosition = false;

		// 确保障碍物不会太靠近出生点
		while (!validPosition)
		{
			obstaclePos.x = xDistribution(engine);
			obstaclePos.y = yDistribution(engine);

			float distance = std::sqrt(std::pow(obstaclePos.x - spawnPoint.x, 2) +
									   std::pow(obstaclePos.y - spawnPoint.y, 2));

			if (distance >= MinDistanceFromSpawn)
			{
				validPosition = true;
			}
		}

		sf::RectangleShape obstacle(sf::Vector2f(40.f, 40.f));
		obstacle.setPosition(obstaclePos);
		obstacle.setFillColor(sf::Color::Red);
		obstacle.setOutlineColor(sf::Color::Black);
		obstacle.setOutlineThickness(2.f);

		obstacles_.push_back(obstacle);
	}
}

void GameScreen::handleInput(sf::RenderWindow &window)
{
	snake_.handleInput(window);
}

void GameScreen::render(sf::RenderWindow &window)
{
	auto &settings = Settings::getInstance();
	window.clear(settings.backgroundColor);
	window.draw(backgroundSprite_);

	// 绘制网格（如果启用）
	if (settings.showGrid)
	{
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

	// 绘制障碍物
	for (const auto &obstacle : obstacles_)
	{
		window.draw(obstacle);
	}

	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
}

void GameScreen::update(sf::Time delta)
{
	generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_, fruitCount_);

	// 检查障碍物碰撞
	if (snake_.checkObstacleCollisions(obstacles_))
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
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
