#pragma once
#include <SFML/Graphics.hpp>
class GameObject
{
public:
	GameObject();
	~GameObject();
	void virtual Update(sf::RenderWindow* window);
	void virtual Draw(sf::RenderWindow* window);
};

