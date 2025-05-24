#include "FruitFactory.h"

using namespace sfSnake;
Fruit FruitFactory::createFruit(sf::Vector2f position, FruitType type)
{
    switch (type)
    {
    case FruitType::Black:
        return Fruit(position, FruitType::Black, 0);
        break;
    case FruitType::Red:
        return Fruit(position, FruitType::Red, 3);
        break;
    case FruitType::Green:
        return Fruit(position, FruitType::Green, 1);
        break;
    case FruitType::Blue:
        return Fruit(position, FruitType::Blue, 2);
        break;
    case FruitType::Brown:
        return Fruit(position, FruitType::Brown, 0);
        break;
    default:
        return Fruit(position, FruitType::Black, 0); // defaul
        break;
    }

    return Fruit(position, FruitType::Black, 0);
}