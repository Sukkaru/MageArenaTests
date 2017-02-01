#pragma once
#include "GameObject.h"
class PhysicsObject : public GameObject
{
public:
	PhysicsObject();
	~PhysicsObject();
	void virtual Update(sf::RenderWindow* window, sf::Time* dt);
	void virtual Draw(sf::RenderWindow* window);
	void ApplyForce(sf::Vector2f force);
	float Magnitude(sf::Vector2f vector);
	sf::Vector2f Normalize(sf::Vector2f vector);
	void CalculateFriction();


protected:
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
	float m_maxMoveSpeed;
	float m_mass;
};

