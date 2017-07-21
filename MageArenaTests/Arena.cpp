#include "stdafx.h"
#include "Arena.h"


Arena::Arena(std::shared_ptr<CollisionManager> collisionmanager, int arenawidth, int arenaheight)
{
	p_colmngr = collisionmanager;
	srand(time(NULL));	//Seed the RNG
	tilewidth = 64;
	tileheight = 64;

	if (!tilemap.loadFromFile("Graphics/stone_tiles.png"))
	{
		printf("Error opening tilemap file!\n");
	}

	//Temp values for testing
	//Pass in constructor later
	this->arenawidth = arenawidth; 
	this->arenaheight = arenaheight;
	
	numtileswide = arenawidth / tilewidth;
	numtileshigh = arenaheight / tileheight;

	//Create arena walls
	p_topouterwall.reset(new Wall(sf::IntRect(0, 0, arenawidth, tileheight), &tilemap, sf::IntRect(64, 64, 64, 64)));
	p_topinnerwall.reset(new Wall(sf::IntRect(0, tileheight, arenawidth, tileheight),sf::FloatRect(0,tileheight,arenawidth,15), &tilemap, sf::IntRect(0, 128, 64, 64)));
	p_rightwall.reset(new Wall(sf::IntRect(arenawidth - tilewidth, tileheight, tilewidth, arenaheight - tileheight), &tilemap, sf::IntRect(64, 64, 64, 64)));
	p_leftwall.reset(new Wall(sf::IntRect(0, tileheight, tilewidth, arenaheight - tileheight), &tilemap, sf::IntRect(64, 64, 64, 64)));
	p_bottomwall.reset(new Wall(sf::IntRect(0, arenaheight - tileheight, arenawidth, tileheight), &tilemap, sf::IntRect(64, 64, 64, 64)));

	//Add the walls to the collision grid
	p_colmngr->addToGrid(p_topouterwall, p_topouterwall->getBBox());
	p_colmngr->addToGrid(p_topinnerwall, p_topinnerwall->getBBox());
	p_colmngr->addToGrid(p_rightwall, p_rightwall->getBBox());
	p_colmngr->addToGrid(p_leftwall, p_leftwall->getBBox());
	p_colmngr->addToGrid(p_bottomwall, p_bottomwall->getBBox());

	//Create the floor of the arena
	createFloor(&tilemap, sf::IntRect(0, 0, 64, 64), numtileswide - 2, numtileshigh - 3,sf::Vector2f(tilewidth,tileheight*2));
}


Arena::~Arena()
{
	
}

void Arena::Draw(sf::RenderWindow * window)
{
	//Add these to the GO vector eventually
	p_topouterwall->Draw(window);
	p_topinnerwall->Draw(window);
	p_rightwall->Draw(window);
	p_leftwall->Draw(window);
	p_bottomwall->Draw(window);

	for (auto row : floorsprites)
	{
		for (auto col : row)
		{
			window->draw(col);
		}
	}
}

void Arena::createFloor(sf::Texture * tilemap, sf::IntRect texturerect, int tileswide, int tileshigh, sf::Vector2f position)
{
	floorsprites = std::vector<std::vector<sf::Sprite> >(tileswide,std::vector<sf::Sprite>(tileshigh));
	for (int row = 0; row < tileswide; row++)
	{
		for (int col = 0; col < tileshigh; col++)
		{
			floorsprites[row][col].setTexture(*tilemap);
			floorsprites[row][col].setTextureRect(texturerect);
			floorsprites[row][col].setPosition(sf::Vector2f(position.x + row * 64, position.y + col * 64));
		}
	}

}
