#pragma once
#include <SFML\Graphics.hpp>
#include "Wall.h"
class Arena
{
public:
	Arena();
	~Arena();
	void Draw(sf::RenderWindow* window);
private:
	sf::Texture tilemap;
	std::vector<std::vector<sf::Vector2i> > arenamap;
	std::vector<std::vector<sf::Sprite> > tiles;
	int tilewidth;
	int tileheight;
	int arenawidth;
	int arenaheight;
	int numtileswide;
	int numtileshigh;

	std::shared_ptr<Wall> p_topouterwall;
	std::shared_ptr<Wall> p_topinnerwall;
	std::shared_ptr<Wall> p_rightwall;
	std::shared_ptr<Wall> p_leftwall;
	std::shared_ptr<Wall> p_bottomwall;

	std::shared_ptr<Wall> p_pillar;
};

