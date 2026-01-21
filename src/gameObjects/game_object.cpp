#include "game_object.h"

GameObject::GameObject(float x, float y)
	: x(x), y(y)
{

}

void GameObject::process()
{

}

void GameObject::setX(float posX) { x = posX; }
void GameObject::setY(float posY) { y = posY; }
float GameObject::getX() const { return x; }
float GameObject::getY() const { return y; }

GameObject::~GameObject()
{

}
