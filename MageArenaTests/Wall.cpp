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
		if (collisionrect.height > 1)
		{
			//otherobject->setVelocity(sf::Vector2f(otherobject->getVelocity().x, -otherobject->getVelocity().y));
			otherobject->setPosition(sf::Vector2f(otherobject->getPosition().x, m_bbox.top + m_bbox.height + 25));
			//printf("Vertical Collision! \n");
		}
	}
	//Horizontal collision
	if (collisionrect.height >= collisionrect.width)
	{
		otherobject->setVelocity(sf::Vector2f(-otherobject->getVelocity().x, otherobject->getVelocity().y));
		printf("Horizontal Collision! \n");
	}
}
