#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
{
	m_destroyed = false;
}


GameObject::~GameObject()
{
}

bool GameObject::getDestroyed()
{
	return m_destroyed;
}

void GameObject::setDestroyed(bool isDestroyed)
{
	m_destroyed = isDestroyed;
}

void GameObject::update(sf::RenderWindow* window, sf::Time* dt)
{

}

void GameObject::draw(sf::RenderWindow* window)
{
}
