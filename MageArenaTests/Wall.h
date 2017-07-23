#pragma once
#include "PhysicsObject.h"
class Wall :
	public PhysicsObject
{
public:
	Wall(sf::IntRect wallRect, sf::FloatRect boundingBox, sf::Texture* wallTexture, sf::IntRect textureRect);
	Wall(sf::IntRect wallRect, sf::Texture* wallTexture, sf::IntRect textureRect);
	
	~Wall();
	void virtual			update(sf::RenderWindow * window, sf::Time* dt);
	void virtual			draw(sf::RenderWindow * window);
	void virtual			resolveCollision(std::shared_ptr<PhysicsObject> otherObject, sf::FloatRect collisionRect);

private:
	int m_nTilesWide;
	int m_nTilesHigh;
	std::vector<std::vector<sf::Sprite> > m_wallTiles;
};

