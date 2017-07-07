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

void Wall::resolveCollision(std::shared_ptr<PhysicsObject> otherobject, sf::FloatRect collisionrect)
{

	printf("Width: %f\n Height: %f\n", collisionrect.width, collisionrect.height);
	//Vertical collision
	if (collisionrect.width >= collisionrect.height)
	{
		//Collision with top side of wall
		if (m_bbox.top - otherobject->getPosition().y > 0)
		{
			otherobject->setVelocity(sf::Vector2f(otherobject->getVelocity().x, -100));		//I just picked the number because it looked good in testing
			otherobject->setPosition(sf::Vector2f(otherobject->getPosition().x, m_bbox.top - otherobject->getEntityHeight() / 2));
			printf("bbox height: %f \n", otherobject->getBBox().top + otherobject->getBBox().height);
			printf("b: %f \n", m_bbox.top);
		}
		//Collision with bottom side of wall
		if ((m_bbox.top + m_bbox.height) - otherobject->getPosition().y < 0)
		{
			otherobject->setVelocity(sf::Vector2f(otherobject->getVelocity().x, 100));		//I just picked the number because it looked good in testing
			otherobject->setPosition(sf::Vector2f(otherobject->getPosition().x, m_bbox.top + m_bbox.height + otherobject->getEntityHeight() / 2));
		}
	}
	//Horizontal collision
	if (collisionrect.height >= collisionrect.width)
	{
		//Collision with left side of wall
		if (m_bbox.left - otherobject->getPosition().x > 0)
		{
			otherobject->setVelocity(sf::Vector2f(-100, otherobject->getVelocity().y));		//I just picked the number because it looked good in testing
			otherobject->setPosition(sf::Vector2f(m_bbox.left - otherobject->getEntityWidth() / 2, otherobject->getPosition().y));
		}
		//Collision with right side of wall
		if ((m_bbox.left + m_bbox.width) - otherobject->getPosition().x < 0)
		{
			otherobject->setVelocity(sf::Vector2f(100, otherobject->getVelocity().y));		//I just picked the number because it looked good in testing
			otherobject->setPosition(sf::Vector2f(m_bbox.left + m_bbox.width + otherobject->getEntityWidth() / 2, otherobject->getPosition().y));
		}
	}
}
