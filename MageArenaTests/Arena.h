#pragma once
#include <SFML\Graphics.hpp>
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

};

