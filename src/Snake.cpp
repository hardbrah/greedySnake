#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

Snake::Snake() : direction_(Direction::Up), hitSelf_(false)
{
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/item-pick-up-38258.mp3");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	// First node is the head
	nodes_.push_back(SnakeNode(sf::Vector2f(
								   Game::Width / 2 - SnakeNode::Width / 2,
								   Game::Height / 2 - (SnakeNode::Height / 2)),
							   true));

	// Rest of the body
	for (int i = 1; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
									   Game::Width / 2 - SnakeNode::Width / 2,
									   Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i)),
								   false));
	}
}

void Snake::handleInput(sf::RenderWindow &window)
{
	// 检查鼠标左键是否按下
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// 获取鼠标在窗口中的位置
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		// 获取蛇头位置
		sf::Vector2f headPos = nodes_[0].getPosition();

		// 计算从蛇头到鼠标的向量
		float dx = mousePos.x - headPos.x;
		float dy = mousePos.y - headPos.y;

		// 计算向量与x轴正方向的夹角（弧度）
		float angle = std::atan2(dy, dx);

		// 转换为角度
		float degrees = angle * 180.0f / 3.14159f;

		// 将角度归一化到0-360范围
		if (degrees < 0)
			degrees += 360.0f;

		// 根据角度设置方向
		if ((degrees >= 315 || degrees < 45) && direction_ != Direction::Left) // 右方向 (-45到45度) 且防止掉头
			direction_ = Direction::Right;
		else if ((degrees >= 45 && degrees < 135) && direction_ != Direction::Up) // 下方向 (45到135度)
			direction_ = Direction::Down;
		else if ((degrees >= 135 && degrees < 225) && direction_ != Direction::Right) // 左方向 (135到225度)
			direction_ = Direction::Left;
		else if (direction_ != Direction::Down) // 上方向 (225到315度)
			direction_ = Direction::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction_ != Direction::Down) // 根据键盘方向键改变方向
	{
		direction_ = Direction::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction_ != Direction::Up)
	{
		direction_ = Direction::Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction_ != Direction::Right)
	{
		direction_ = Direction::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction_ != Direction::Left)
	{
		direction_ = Direction::Right;
	}
}

void Snake::update(sf::Time delta)
{
	move(delta);
	nodes_[0].setDirection(direction_);
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit> &fruits, FruitCount &fruitCount)
{
	std::vector<decltype(fruits.begin())> toRemove;

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
		{
			toRemove.push_back(it);
			pickupSound_.play();
			grow(it->getGrowth());
		}
	}

	for (auto it = toRemove.rbegin(); it != toRemove.rend(); ++it)
	{
		switch ((*it)->getColor())
		{
		case FruitType::Black:
			fruitCount.black++;
			break;
		case FruitType::Blue:
			fruitCount.blue++;
			break;
		case FruitType::Brown:
			fruitCount.brown++;
			break;
		case FruitType::Green:
			fruitCount.green++;
			break;
		case FruitType::Red:
			fruitCount.red++;
			break;
		default:
			break;
		}
		fruits.erase(*it);
	}
}

void Snake::grow(unsigned short growth)
{
	for (unsigned i = 0; i < growth; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x, nodes_[nodes_.size() - 1].getPosition().y)));
	}
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode &headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 1; i < nodes_.size(); ++i)
	{
		if (headNode.getBounds().intersects(nodes_[i].getBounds()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode &headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move(sf::Time delta)
{
	static std::vector<int> moveDelays(nodes_.size(), 0);

	// Resize moveDelays if new nodes are added
	if (moveDelays.size() < nodes_.size())
	{
		int newNodeCount = nodes_.size() - moveDelays.size();
		for (int i = 0; i < newNodeCount; ++i)
		{
			moveDelays.push_back(i + 1); // add delay for new nodes
		}
	}

	// Move nodes that are ready (delay is 0)
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		if (moveDelays[i] > 0)
		{
			moveDelays[i]--;
			continue;
		}
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
	}

	// head always moves
	switch (direction_)
	{
	case Direction::Up:
		nodes_[0].move(0, -SnakeNode::Height);
		break;
	case Direction::Down:
		nodes_[0].move(0, SnakeNode::Height);
		break;
	case Direction::Left:
		nodes_[0].move(-SnakeNode::Width, 0);
		break;
	case Direction::Right:
		nodes_[0].move(SnakeNode::Width, 0);
		break;
	}
}

void Snake::render(sf::RenderWindow &window)
{
	for (auto &node : nodes_)
		node.render(window);
}
