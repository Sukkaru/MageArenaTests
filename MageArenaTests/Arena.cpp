#include "stdafx.h"
#include "Arena.h"


Arena::Arena()
{
	
	tilewidth = 64;
	tileheight = 64;
	if (!tilemap.loadFromFile("Graphics/stone_tiles.png"))
	{
		printf("Error opening tilemap file!\n");
	}

	//Temp values for testing
	//Pass in constructor later
	arenawidth = 1280;
	arenaheight = 768;
	
	//Create arena map here, will be in a function later
	numtileswide = arenawidth / tilewidth;
	numtileshigh = arenaheight / tileheight;

	arenamap = std::vector<std::vector<sf::Vector2i>>(numtileshigh, std::vector<sf::Vector2i>(numtileswide));
	tiles = std::vector<std::vector<sf::Sprite>>(numtileshigh, std::vector<sf::Sprite>(numtileswide));
	for (int row = 0; row < numtileshigh; row++)
	{
		for (int col = 0; col < numtileswide; col++)
		{
			arenamap[row][col].x = rand() % 2;		//Temp value for testing
			arenamap[row][col].y = rand() % 2;
		}
	}

	//Set sprite textures here, will be in a function later
	for (int row = 0; row < numtileshigh; row++)
	{
		for (int col = 0; col < numtileswide; col++)
		{
			tiles[row][col].setTexture(tilemap);		
			tiles[row][col].setTextureRect(sf::IntRect(arenamap[row][col].x * 64, arenamap[row][col].y * 64, 64, 64));	//Temp values for testing
			tiles[row][col].setPosition(sf::Vector2f(col * 64, row * 64));
		}
	}


}


Arena::~Arena()
{
}

void Arena::Draw(sf::RenderWindow * window)
{
	for (int row = 0; row < numtileshigh; row++)
	{
		for (int col = 0; col < numtileswide; col++)
		{
			window->draw(tiles[row][col]);
		}
	}
}
