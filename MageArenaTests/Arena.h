#pragma once
#include <SFML\Graphics.hpp>
#include "Wall.h"
#include "CollisionManager.h"
class Arena
{
public:
	Arena(std::shared_ptr<CollisionManager> p_colmngr);
	~Arena();
	void Draw(sf::RenderWindow* window);
private:
	void createFloor(sf::Texture* tilemap, sf::IntRect texturerect, int tileswide, int tileshigh, sf::Vector2f position);


	sf::Texture tilemap;
	std::vector<std::vector<sf::Vector2i> > floortiles;
	std::vector<std::vector<sf::Sprite> > floorsprites;
	int tilewidth;
	int tileheight;
	int arenawidth;
	int arenaheight;
	int numtileswide;
	int numtileshigh;

	std::shared_ptr<CollisionManager> p_colmngr;

	std::shared_ptr<Wall> p_topouterwall;
	std::shared_ptr<Wall> p_topinnerwall;
	std::shared_ptr<Wall> p_rightwall;
	std::shared_ptr<Wall> p_leftwall;
	std::shared_ptr<Wall> p_bottomwall;

	std::shared_ptr<Wall> p_pillar;
};

