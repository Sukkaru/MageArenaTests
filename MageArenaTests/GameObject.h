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
	int				getCollisionGroup() { return collisiongroup; }
	unsigned char	getCollidableGroups() { return collidablegroups; }
protected:
	bool			m_destroyed = false;
	int				collisiongroup = 0;				//Default: Not part of any collision group
	unsigned char	collidablegroups = 0;			//Default: Can't collide with anything
};

