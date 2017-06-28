#pragma once
#include "PhysicsObject.h"
class Wall :
	public PhysicsObject
{
public:
	Wall(sf::IntRect wallrect, sf::Texture* walltexture, sf::IntRect texturerect);
	~Wall();
	void Update(sf::RenderWindow * window, sf::Time* dt);
	void Draw(sf::RenderWindow * window);

private:
	int numtileswide;
	int numtileshigh;
	std::vector<std::vector<sf::Sprite> > walltiles;
};

