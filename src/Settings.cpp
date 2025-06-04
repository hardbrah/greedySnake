// Settings.cpp
#include "Settings.h"

using namespace sfSnake;

Settings &Settings::getInstance()
{
    static Settings instance;
    return instance;
}
