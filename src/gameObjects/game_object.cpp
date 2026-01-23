#include "game_object.h"

#include <iostream>

GameObject::GameObject(float x, float y, bool isAlive)
	: x(x), y(y), isAlive(isAlive)
{

}

void GameObject::process() {}
void GameObject::draw() {}

void GameObject::setX(float posX) { x = posX; }
void GameObject::setY(float posY) { y = posY; }

Vector2 GameObject::getPos() const { return {x, y}; }
float GameObject::getRotation() const { return 0.0f; }

GameObject::~GameObject()
{
    std::cout << "GameObject deleted\n";
}
