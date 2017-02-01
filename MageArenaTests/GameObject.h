#pragma once
#include <SFML/Graphics.hpp>
class GameObject
{
public:
	GameObject();
	~GameObject();
	void virtual Update(sf::RenderWindow* window, sf::Time* dt);
	void virtual Draw(sf::RenderWindow* window);
};

