#ifndef FRUITFACTORY_H
#define FRUITFACTORY_H
#include "Fruit.h"

namespace sfSnake
{
    class FruitFactory
    {
    public:
        FruitFactory() = delete;
        static Fruit createFruit(sf::Vector2f position, FruitType type);
    };
}
// end of Fruit.h
#endif