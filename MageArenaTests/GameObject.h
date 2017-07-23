#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject();
	void virtual	update(sf::RenderWindow* window, sf::Time* dt);
	void virtual	draw(sf::RenderWindow* window);

	bool			getDestroyed();
	void			setDestroyed(bool isDestroyed);

protected:
	bool			m_destroyed;
};

