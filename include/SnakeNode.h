#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
	enum Direction
	{
		Up,
		Right,
		Down,
		Left
	};
	class SnakeNode
	{
	public:
		SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0), bool isHead = false);

		void setPosition(sf::Vector2f position);
		void setPosition(float x, float y);

		void move(float xOffset, float yOffset);

		void render(sf::RenderWindow &window);

		sf::Vector2f getPosition() const;
		sf::FloatRect getBounds() const;

		static const float Width;
		static const float Height;

		void setDirection(Direction direction);

	private:
		sf::RectangleShape shape_;
		sf::Vector2f position_;
		bool isHead_;
		sf::Texture headTexture_;
		sf::Sprite headSprite_;
		sf::Texture bodyTexture_;
		sf::Sprite bodySprite_;
		Direction direction_; // To rotate the head sprite based on direction
	};
}

#endif