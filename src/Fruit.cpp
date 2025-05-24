#include <SFML/Graphics.hpp>

#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 5.f;

Fruit::Fruit(sf::Vector2f position, FruitType color, unsigned short growth)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	switch (color)
	{
	case FruitType::Black:
		shape_.setFillColor(sf::Color::Black);
		break;
	case FruitType::Blue:
		shape_.setFillColor(sf::Color::Blue);
		break;
	case FruitType::Brown:
		shape_.setFillColor(sf::Color(139, 69, 19));
		break;
	case FruitType::Green:
		shape_.setFillColor(sf::Color::Green);
		break;
	case FruitType::Red:
		shape_.setFillColor(sf::Color::Red);
		break;
	default:
		shape_.setFillColor(sf::Color::White);
		break;
	}
	color_ = color;
	growth_ = growth;
}
FruitType Fruit::getColor() const
{
	return color_;
}
void Fruit::render(sf::RenderWindow &window)
{
	window.draw(shape_);
}

unsigned short Fruit::getGrowth() const
{
	return growth_;
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}