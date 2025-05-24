#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
	enum class FruitType
	{
		Red,
		Green,
		Blue,
		Black,
		Brown
	};
	class Fruit
	{
	public:
		Fruit(sf::Vector2f position = sf::Vector2f(0, 0), FruitType color = FruitType::Black, unsigned short growth = 0);

		void render(sf::RenderWindow &window);

		sf::FloatRect getBounds() const;
		unsigned short getGrowth() const;
		FruitType getColor() const;

	private:
		sf::CircleShape shape_;

		static const float Radius;
		FruitType color_;
		unsigned short growth_;
	};
}

#endif