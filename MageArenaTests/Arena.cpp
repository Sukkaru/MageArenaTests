#include "stdafx.h"
#include "Arena.h"


Arena::Arena(std::shared_ptr<CollisionManager> collisionManager, int arenaWidth, int arenaHeight)
{
	m_collisionManager = collisionManager;
	srand(time(NULL));	//Seed the RNG
	m_tileWidth = 64;
	m_tileHeight = 64;

	if (!m_tilesTexture.loadFromFile("Graphics/stone_tiles.png"))
	{
		printf("Error opening tilemap file!\n");
	}

	//Temp values for testing
	//Pass in constructor later
	m_arenaWidth = arenaWidth; 
	m_arenaHeight = arenaHeight;
	
	m_nTilesWide = arenaWidth / m_tileWidth;
	m_nTilesHigh = arenaHeight / m_tileHeight;

	//Create arena walls
	m_topOuterWall.reset(new Wall(sf::IntRect(0, 0, arenaWidth, m_tileHeight), &m_tilesTexture, sf::IntRect(64, 64, 64, 64)));
	m_topInnerWall.reset(new Wall(sf::IntRect(0, m_tileHeight, arenaWidth, m_tileHeight),sf::FloatRect(0, m_tileHeight, arenaWidth,15), &m_tilesTexture, sf::IntRect(0, 128, 64, 64)));
	m_rightWall.reset(new Wall(sf::IntRect(arenaWidth - m_tileWidth, m_tileHeight, m_tileWidth, arenaHeight - m_tileHeight), &m_tilesTexture, sf::IntRect(64, 64, 64, 64)));
	m_leftWall.reset(new Wall(sf::IntRect(0, m_tileHeight, m_tileWidth, arenaHeight - m_tileHeight), &m_tilesTexture, sf::IntRect(64, 64, 64, 64)));
	m_bottomWall.reset(new Wall(sf::IntRect(0, arenaHeight - m_tileHeight, arenaWidth, m_tileHeight), &m_tilesTexture, sf::IntRect(64, 64, 64, 64)));

	//Add the walls to the collision grid
	m_collisionManager->addToGrid(m_topOuterWall, m_topOuterWall->getBoundingBox());
	m_collisionManager->addToGrid(m_topInnerWall, m_topInnerWall->getBoundingBox());
	m_collisionManager->addToGrid(m_rightWall, m_rightWall->getBoundingBox());
	m_collisionManager->addToGrid(m_leftWall, m_leftWall->getBoundingBox());
	m_collisionManager->addToGrid(m_bottomWall, m_bottomWall->getBoundingBox());

	//Create the floor of the arena
	createFloor(&m_tilesTexture, sf::IntRect(0, 0, 64, 64), m_nTilesWide - 2, m_nTilesHigh - 3,sf::Vector2f(m_tileWidth,m_tileHeight*2));
}


Arena::~Arena()
{
	
}

void Arena::draw(sf::RenderWindow * window)
{
	//Add these to the GO vector eventually
	m_topOuterWall->draw(window);
	m_topInnerWall->draw(window);
	m_rightWall->draw(window);
	m_leftWall->draw(window);
	m_bottomWall->draw(window);

	for (auto row : m_floorSprites)
	{
		for (auto col : row)
		{
			window->draw(col);
		}
	}
}

void Arena::createFloor(sf::Texture * tilesTexture, sf::IntRect textureRect, int nTilesWide, int nTilesHigh, sf::Vector2f position)
{
	m_floorSprites = std::vector<std::vector<sf::Sprite> >(nTilesWide,std::vector<sf::Sprite>(nTilesHigh));
	for (int row = 0; row < nTilesWide; row++)
	{
		for (int col = 0; col < nTilesHigh; col++)
		{
			m_floorSprites[row][col].setTexture(*tilesTexture);
			m_floorSprites[row][col].setTextureRect(textureRect);
			m_floorSprites[row][col].setPosition(sf::Vector2f(position.x + row * 64, position.y + col * 64));
		}
	}

}
