#pragma once
#include "PhysicsObject.h"
#include "Fireball.h"
#include <SFML/Graphics.hpp>
class Player : public PhysicsObject
{
public:
	Player();
	~Player();
	void virtual Update(sf::RenderWindow* window, sf::Clock* clock);
	void virtual Draw(sf::RenderWindow* window);

private:
	sf::RectangleShape m_playerBody;
	sf::RectangleShape m_aimer;		//For player aiming, points toward mouse position

};

