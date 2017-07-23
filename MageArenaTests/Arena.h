#pragma once
#include <SFML\Graphics.hpp>
#include "Wall.h"
#include "CollisionManager.h"
class Arena
{
public:
	Arena(std::shared_ptr<CollisionManager> collisionManager, int arenaWidth, int arenaHeight);
	~Arena();
	void draw(sf::RenderWindow* window);
private:
	void createFloor(sf::Texture* tileMap, sf::IntRect textureRect, int nTilesWide, int nTilesHigh, sf::Vector2f position);


	sf::Texture m_tilesTexture;
	std::vector<std::vector<sf::Vector2i> > m_floorTiles;
	std::vector<std::vector<sf::Sprite> > m_floorSprites;
	int m_tileWidth;
	int m_tileHeight;
	int m_arenaWidth;
	int m_arenaHeight;
	int m_nTilesWide;
	int m_nTilesHigh;

	std::shared_ptr<CollisionManager> m_collisionManager;

	std::shared_ptr<Wall> m_topOuterWall;
	std::shared_ptr<Wall> m_topInnerWall;
	std::shared_ptr<Wall> m_rightWall;
	std::shared_ptr<Wall> m_leftWall;
	std::shared_ptr<Wall> m_bottomWall;

	std::shared_ptr<Wall> m_pillar;
};

