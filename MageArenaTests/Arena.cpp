#include "stdafx.h"
#include "Arena.h"


Arena::Arena()
{
	srand(time(NULL));	//Seed the RNG
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
	
	//Create arena walls
	p_topouterwall.reset(new Wall(sf::IntRect(0, 0, arenawidth, tileheight), &tilemap, sf::IntRect(64, 64, 64, 64)));
	p_topinnerwall.reset(new Wall(sf::IntRect(0, tileheight, arenawidth, tileheight), &tilemap, sf::IntRect(0, 128, 64, 64)));
	p_rightwall.reset(new Wall(sf::IntRect(arenawidth - tilewidth, tileheight, tilewidth, arenaheight - tileheight), &tilemap, sf::IntRect(64, 64, 64, 64)));
	p_leftwall.reset(new Wall(sf::IntRect(0, tileheight, tilewidth, arenaheight - tileheight), &tilemap, sf::IntRect(64, 64, 64, 64)));
	p_bottomwall.reset(new Wall(sf::IntRect(0, arenaheight - tileheight, arenawidth, tileheight), &tilemap, sf::IntRect(64, 64, 64, 64)));
	p_pillar.reset(new Wall(sf::IntRect(arenawidth/2, arenaheight / 2, tilewidth, tileheight), &tilemap, sf::IntRect(64, 64, 64, 64)));
}


Arena::~Arena()
{
}

void Arena::Draw(sf::RenderWindow * window)
{
	p_topouterwall->Draw(window);
	p_topinnerwall->Draw(window);
	p_rightwall->Draw(window);
	p_leftwall->Draw(window);
	p_bottomwall->Draw(window);
	p_pillar->Draw(window);
}
