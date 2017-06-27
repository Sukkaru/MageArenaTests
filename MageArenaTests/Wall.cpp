#include "stdafx.h"
#include "Wall.h"


Wall::Wall(sf::IntRect wallrect, sf::Texture* walltexture, sf::IntRect texturerect)
{
	numtileswide = wallrect.width / texturerect.width;
	numtileshigh = wallrect.height / texturerect.height;
	walltiles = std::vector<std::vector<sf::Sprite>>(numtileshigh, std::vector<sf::Sprite>(numtileswide));

	for (int row = 0; row < numtileshigh; row++)
	{
		for (int col = 0; col < numtileswide; col++)
		{
			walltiles[row][col].setTexture(*walltexture);		
			walltiles[row][col].setTextureRect(texturerect);	
			walltiles[row][col].setPosition(sf::Vector2f(wallrect.left + (col * texturerect.width),wallrect.top + (row * texturerect.height) ));
		}
	}

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
