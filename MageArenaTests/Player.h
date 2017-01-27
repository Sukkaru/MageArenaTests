#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
class Player : public GameObject
{
public:
	Player();
	~Player();
	void virtual Update(sf::RenderWindow* window, sf::Clock* clock);
	void virtual Draw(sf::RenderWindow* window);
	void ApplyForce(sf::Vector2f force);

private:
	sf::RectangleShape m_playerBody;
	sf::RectangleShape m_aimer;		//For player aiming, points toward mouse position
	sf::Vector2f m_upForce;		//For moving up
	sf::Vector2f m_downForce;	//For moving down
	sf::Vector2f m_rightForce;  //For moving right
	sf::Vector2f m_leftForce;   //For moving left

	sf::Vector2f m_accel;		//Acceleration
	sf::Vector2f m_velocity;
	float normalForce;
	float frictionCoeff;
	sf::Vector2f m_friction;
	float m_moveSpeed;
	float m_mass;
};

