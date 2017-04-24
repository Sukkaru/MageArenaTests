#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Update(sf::RenderWindow* window, sf::Time* dt)
{
	printf("In GameObject Update\n");
}

void GameObject::Draw(sf::RenderWindow* window)
{
}
