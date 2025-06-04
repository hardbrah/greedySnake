#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"
#include "FruitFactory.h"
#include "FruitCount.h"

namespace sfSnake
{
	class GameScreen : public Screen
	{
	public:
		GameScreen();

		void handleInput(sf::RenderWindow &window) override;
		void update(sf::Time delta) override;
		void render(sf::RenderWindow &window) override;

		void generateFruit();

	private:
		void generateFruit_(FruitType type);
		void generateObstacles(); // 新增：生成障碍物方法

		Snake snake_;
		std::vector<Fruit> fruit_;
		FruitCount fruitCount_;
		sf::Texture backgroundTexture_;
		sf::Sprite backgroundSprite_;
		bool grid_;
		sf::Color gridColor_;

		// 新增：障碍物相关
		std::vector<sf::RectangleShape> obstacles_;
		static const int ObstacleCount = 5;		 // 障碍物数量
		static const float MinDistanceFromSpawn; // 距离出生点的最小距离
	};
}

#endif