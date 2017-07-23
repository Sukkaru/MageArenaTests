#pragma once
#include <SFML\Graphics.hpp>
class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u textureRectSize, float switchTime);
	~Animation();

	void					update(float dt, int row, int endColumn, int startColumn = 0);
	sf::IntRect				getTextureRect();
private:
	sf::Vector2u			m_currentImage;

	float					m_totalTime;
	float					m_switchTime;
	sf::IntRect				m_textureRect;

};

