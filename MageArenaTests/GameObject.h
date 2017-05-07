#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject();
	void virtual	Update(sf::RenderWindow* window, sf::Time* dt);
	void virtual	Draw(sf::RenderWindow* window);

	bool			getDestroyed() { return m_destroyed; }
	void			setDestroyed(bool input) { m_destroyed = input; }

protected:
	bool			m_destroyed = true;
};

