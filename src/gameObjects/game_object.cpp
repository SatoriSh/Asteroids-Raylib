#include "game_object.h"

#include <iostream>

GameObject::GameObject(float x, float y)
	: x(x), y(y)
{

}

void GameObject::process()
{

}

void GameObject::setX(float posX) { x = posX; }
void GameObject::setY(float posY) { y = posY; }

Vector2 GameObject::getPos() const { return {x, y}; }

GameObject::~GameObject()
{
    std::cout << "GameObject deleted\n";
}
