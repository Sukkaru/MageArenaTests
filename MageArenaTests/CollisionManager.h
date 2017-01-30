#pragma once
#include <SFML\Graphics.hpp>
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	//Using rectangles for now, change to something else later
	void AddCollider(sf::RectangleShape* collider);
};

