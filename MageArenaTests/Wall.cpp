#include "stdafx.h"
#include "Wall.h"


Wall::Wall(sf::IntRect wallrect,sf::Texture* walltexture, sf::IntRect texturerect)
{
	numtileswide = wallrect.width / texturerect.width;
	numtileshigh = wallrect.height / texturerect.height;
	walltiles = std::vector<std::vector<sf::Sprite>>(numtileshigh, std::vector<sf::Sprite>(numtileswide));

	//Set wall tile textures
	for (int row = 0; row < numtileshigh; row++)
	{
		for (int col = 0; col < numtileswide; col++)
		{
			walltiles[row][col].setTexture(*walltexture);		
			walltiles[row][col].setTextureRect(texturerect);	
			walltiles[row][col].setPosition(sf::Vector2f(wallrect.left + (col * texturerect.width),wallrect.top + (row * texturerect.height) ));
		}
	}

	m_bbox = sf::FloatRect(wallrect);
	m_prevbbox = m_bbox;
	m_collisiongroup = 2;		//Terrain collision group
	m_collidablegroups = 26;	//Groups terrain can collide with, 2^1 = 2, 2^3 = 8, 2^4 = 16, Player, Enemy, Spell 

}

Wall::Wall(sf::IntRect wallrect, sf::FloatRect boundingbox, sf::Texture * walltexture, sf::IntRect texturerect) : Wall(wallrect, walltexture, texturerect)
{
	m_bbox = boundingbox;
	m_prevbbox = m_bbox;
}


Wall::~Wall()
{
}

void Wall::Update(sf::RenderWindow * window, sf::Time * dt)
{
}

void Wall::Draw(sf::RenderWindow * window)
{
	for (int row = 0; row < numtileshigh; row++)
	{
		for (int col = 0; col < numtileswide; col++)
		{
			window->draw(walltiles[row][col]);
		}
	}
}

void Wall::resolveCollision(std::shared_ptr<PhysicsObject> otherobject)
{
	//This code might change in the future
	float wallleft = m_bbox.left;
	float wallright = m_bbox.left + m_bbox.width;
	float walltop = m_bbox.top;
	float wallbot = m_bbox.top + m_bbox.height;
	//Collide right
	if (otherobject->getPrevBBox().left > wallright && otherobject->getBBox().left <= wallright)
	{
		otherobject->setVelocity(sf::Vector2f(0, otherobject->getVelocity().y));
	}
	//Collide left
	if (otherobject->getPrevBBox().left + otherobject->getPrevBBox().width < wallleft && otherobject->getBBox().left + otherobject->getBBox().width >= wallleft)
	{
		otherobject->setVelocity(sf::Vector2f(0, otherobject->getVelocity().y));
	}
	//Collide top
	if (otherobject->getPrevBBox().top + otherobject->getPrevBBox().height < walltop && otherobject->getBBox().top + otherobject->getBBox().height >= walltop)
	{
		otherobject->setVelocity(sf::Vector2f(otherobject->getVelocity().x, 0));
	}
	//Collide bottom
	if (otherobject->getPrevBBox().top > wallbot && otherobject->getBBox().top <= wallbot)
	{
		otherobject->setVelocity(sf::Vector2f(otherobject->getVelocity().x, 0));
	}
}
