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
		Snake snake_;
		std::vector<Fruit> fruit_;
		FruitCount fruitCount_;
		sf::Texture backgroundTexture_;
		sf::Sprite backgroundSprite_;
		bool grid_;
		sf::Color gridColor_;
	};
}

#endif