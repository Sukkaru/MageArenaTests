#pragma once
#include <SFML\Graphics.hpp>
class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u texturerectsize, float switchtime);
	~Animation();

	void Update(float dt, int row, int endcol, int startcol = 0);
	sf::IntRect getTextureRect();
private:
	sf::Vector2u currentimage;

	float totaltime;
	float switchtime;
	sf::IntRect texturerect;

};

