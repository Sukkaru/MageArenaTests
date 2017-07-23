#include "stdafx.h"
#include "Wall.h"


Wall::Wall(sf::IntRect wallRect,sf::Texture* wallTexture, sf::IntRect textureRect)
{
	m_nTilesWide = wallRect.width / textureRect.width;
	m_nTilesHigh = wallRect.height / textureRect.height;
	m_wallTiles = std::vector<std::vector<sf::Sprite>>(m_nTilesHigh, std::vector<sf::Sprite>(m_nTilesWide));

	//Set wall tile textures
	for (int row = 0; row < m_nTilesHigh; row++)
	{
		for (int col = 0; col < m_nTilesWide; col++)
		{
			m_wallTiles[row][col].setTexture(*wallTexture);		
			m_wallTiles[row][col].setTextureRect(textureRect);	
			m_wallTiles[row][col].setPosition(sf::Vector2f((float)(wallRect.left + (col * textureRect.width)), (float)(wallRect.top + (row * textureRect.height))));
		}
	}

	m_boundingBox = sf::FloatRect(wallRect);
	m_previousBoundingBox = m_boundingBox;
	m_collisionGroup = 2;		//Terrain collision group
	m_collidableGroups = 26;	//Groups terrain can collide with, 2^1 = 2, 2^3 = 8, 2^4 = 16, Player, Enemy, Spell 

}

Wall::Wall(sf::IntRect wallRect, sf::FloatRect boundingBox, sf::Texture * wallTexture, sf::IntRect textureRect) : Wall(wallRect, wallTexture, textureRect)
{
	m_boundingBox = boundingBox;
	m_previousBoundingBox = m_boundingBox;
}


Wall::~Wall()
{
}

void Wall::update(sf::RenderWindow * window, sf::Time * dt)
{
}

void Wall::draw(sf::RenderWindow * window)
{
	for (int row = 0; row < m_nTilesHigh; row++)
	{
		for (int col = 0; col < m_nTilesWide; col++)
		{
			window->draw(m_wallTiles[row][col]);
		}
	}
}

void Wall::resolveCollision(std::shared_ptr<PhysicsObject> otherObject, sf::FloatRect collisionRect)
{

	//printf("Width: %f\n Height: %f\n", collisionrect.width, collisionrect.height);
	//Vertical collision
	if (collisionRect.width >= collisionRect.height)
	{
		//Collision with top side of wall
		if (m_boundingBox.top - otherObject->getPosition().y > 0)
		{
			otherObject->setVelocity(sf::Vector2f(otherObject->getVelocity().x, -10));		//I just picked the number because it looked good in testing
			otherObject->setPosition(sf::Vector2f(otherObject->getPosition().x, m_boundingBox.top - otherObject->getEntityHeight() / 2));
			//printf("bbox height: %f \n", otherobject->getBBox().top + otherobject->getBBox().height);
			//printf("b: %f \n", m_bbox.top);
		}
		//Collision with bottom side of wall
		if ((m_boundingBox.top + m_boundingBox.height) - otherObject->getPosition().y < 0)
		{
			otherObject->setVelocity(sf::Vector2f(otherObject->getVelocity().x, 10));		//I just picked the number because it looked good in testing
			otherObject->setPosition(sf::Vector2f(otherObject->getPosition().x, m_boundingBox.top + m_boundingBox.height + otherObject->getEntityHeight() / 2));
		}
	}
	//Horizontal collision
	if (collisionRect.height >= collisionRect.width)
	{
		//Collision with left side of wall
		if (m_boundingBox.left - otherObject->getPosition().x > 0)
		{
			otherObject->setVelocity(sf::Vector2f(-10, otherObject->getVelocity().y));		//I just picked the number because it looked good in testing
			otherObject->setPosition(sf::Vector2f(m_boundingBox.left - otherObject->getEntityWidth() / 2, otherObject->getPosition().y));
		}
		//Collision with right side of wall
		if ((m_boundingBox.left + m_boundingBox.width) - otherObject->getPosition().x < 0)
		{
			otherObject->setVelocity(sf::Vector2f(10, otherObject->getVelocity().y));		//I just picked the number because it looked good in testing
			otherObject->setPosition(sf::Vector2f(m_boundingBox.left + m_boundingBox.width + otherObject->getEntityWidth() / 2, otherObject->getPosition().y));
		}
	}
}
