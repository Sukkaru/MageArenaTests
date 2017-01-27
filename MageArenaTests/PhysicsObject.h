#pragma once
#include "GameObject.h"
class PhysicsObject : public GameObject
{
public:
	PhysicsObject();
	~PhysicsObject();
	void ApplyForce(sf::Vector2f force);


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
	float m_mass;
};

