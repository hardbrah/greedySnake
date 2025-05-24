#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "SnakeNode.h"
#include "Fruit.h"
#include "FruitCount.h"
#include <cmath>
#include "Game.h"

namespace sfSnake
{

	class Snake
	{
	public:
		Snake();

		// 修改handleInput函数声明
		void handleInput(sf::RenderWindow &window);
		void update(sf::Time delta);
		void render(sf::RenderWindow &window);

		void checkFruitCollisions(std::vector<Fruit> &fruits, FruitCount &fruitCount);

		bool hitSelf() const;

		unsigned getSize() const;

	private:
		void move(sf::Time delta);
		void grow(unsigned short growth);
		void checkEdgeCollisions();
		void checkSelfCollisions();
		void initNodes();

		bool hitSelf_;

		sf::Vector2f position_;
		Direction direction_;

		sf::SoundBuffer pickupBuffer_;
		sf::Sound pickupSound_;

		sf::SoundBuffer dieBuffer_;
		sf::Sound dieSound_;

		std::vector<SnakeNode> nodes_;

		static const int InitialSize;
	};
}

#endif