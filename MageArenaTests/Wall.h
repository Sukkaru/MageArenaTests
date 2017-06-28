#pragma once
#include "PhysicsObject.h"
class Wall :
	public PhysicsObject
{
public:
	Wall(sf::IntRect wallrect, sf::Texture* walltexture, sf::IntRect texturerect);
	~Wall();
	void virtual			Update(sf::RenderWindow * window, sf::Time* dt);
	void virtual			Draw(sf::RenderWindow * window);
	void virtual			resolveCollision(std::shared_ptr<PhysicsObject> otherobject);

private:
	int numtileswide;
	int numtileshigh;
	std::vector<std::vector<sf::Sprite> > walltiles;
};

