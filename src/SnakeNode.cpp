#include <SFML/Graphics.hpp>

#include "SnakeNode.h"
#include <iostream>

using namespace sfSnake;

const float SnakeNode::Width = 10.f;
const float SnakeNode::Height = 10.f;

SnakeNode::SnakeNode(sf::Vector2f position, bool isHead)
	: position_(position), isHead_(isHead), direction_(Direction::Up)
{
	shape_.setPosition(position_);
	shape_.setFillColor(sf::Color::Green);
	shape_.setSize(sf::Vector2f(SnakeNode::Width, SnakeNode::Height));
	shape_.setOutlineColor(sf::Color::White);
	shape_.setOutlineThickness(-1.f);

	if (isHead_)
	{
		// Load the head texture
		if (!headTexture_.loadFromFile("Images/up.png"))
		{
			// Fallback if image loading fails
			isHead_ = false;
			std::cout << "Failed to load image" << std::endl;
			return;
		}

		// Setup the sprite
		headSprite_.setTexture(headTexture_);

		// Scale the sprite to match the snake node size
		headSprite_.setScale(SnakeNode::Width / headTexture_.getSize().x, SnakeNode::Height / headTexture_.getSize().y);

		// Set the origin to the center for proper rotation
		headSprite_.setOrigin(headTexture_.getSize().x / 2.f, headTexture_.getSize().y / 2.f);

		// Position the sprite
		headSprite_.setPosition(position_.x + SnakeNode::Width / 2.f, position_.y + SnakeNode::Height / 2.f);
	}
	else
	{
		if (!bodyTexture_.loadFromFile("Images/snake_green_blob_32.png"))
		{
			// Fallback if image loading fails
			std::cout << "Failed to load image" << std::endl;
			return;
		}
		bodySprite_.setTexture(bodyTexture_);
		bodySprite_.setScale(SnakeNode::Width / bodyTexture_.getSize().x, SnakeNode::Height / bodyTexture_.getSize().y);
		bodySprite_.setOrigin(bodyTexture_.getSize().x / 2.f, bodyTexture_.getSize().y / 2.f);
		bodySprite_.setPosition(position_.x + SnakeNode::Width / 2.f, position_.y + SnakeNode::Height / 2.f);
	}
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);

	if (isHead_)
	{
		headSprite_.setPosition(position_.x + SnakeNode::Width / 2.f, position_.y + SnakeNode::Height / 2.f);
	}
	else
	{
		bodySprite_.setPosition(position_.x + SnakeNode::Width / 2.f, position_.y + SnakeNode::Height / 2.f);
	}
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);

	if (isHead_)
	{
		headSprite_.setPosition(position_.x + SnakeNode::Width / 2.f, position_.y + SnakeNode::Height / 2.f);
	}
	else
	{
		bodySprite_.setPosition(position_.x + SnakeNode::Width / 2.f, position_.y + SnakeNode::Height / 2.f);
	}
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	shape_.setPosition(position_);

	if (isHead_)
	{
		headSprite_.setPosition(position_.x + SnakeNode::Width / 2.f, position_.y + SnakeNode::Height / 2.f);
	}
	else
	{
		bodySprite_.setPosition(position_.x + SnakeNode::Width / 2.f, position_.y + SnakeNode::Height / 2.f);
	}
}

sf::FloatRect SnakeNode::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::setDirection(Direction direction)
{
	if (!isHead_)
		return;
	// Rotate the head sprite based on direction
	direction_ = direction;
	switch (direction_)
	{
	case Direction::Up: // Up
		headSprite_.setRotation(0);
		break;
	case Direction::Right: // Right
		headSprite_.setRotation(90);
		break;
	case Direction::Down: // Down
		headSprite_.setRotation(180);
		break;
	case Direction::Left: // Left
		headSprite_.setRotation(270);
		break;
	}
}

void SnakeNode::render(sf::RenderWindow &window)
{
	if (isHead_)
	{
		headSprite_.setTexture(headTexture_);
		window.draw(headSprite_);
	}
	else
	{
		bodySprite_.setTexture(bodyTexture_);
		window.draw(bodySprite_);
	}
}