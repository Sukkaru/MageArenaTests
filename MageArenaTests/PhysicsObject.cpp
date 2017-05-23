#include "stdafx.h"
#include "PhysicsObject.h"


PhysicsObject::PhysicsObject()
{
	
}


PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::Update(sf::RenderWindow * window, sf::Time* dt)
{
}

void PhysicsObject::Draw(sf::RenderWindow * window)
{
}

void PhysicsObject::ApplyForce(sf::Vector2f force)
{
	//Scaling the vector down by the mass
	force /= m_mass;
	m_accel += force;
}

float PhysicsObject::Magnitude(sf::Vector2f vector)
{
	//Raising to the power of .5f is the same as taking the square root
	float temp = powf((vector.x * vector.x) + (vector.y * vector.y),0.5f);
	//printf("Magnitude: %f\n", temp);
	return temp;
}

sf::Vector2f PhysicsObject::Normalize(sf::Vector2f vector)
{
	float mag = Magnitude(vector);
	if (mag > 0.0)
	{
		sf::Vector2f normVector = sf::Vector2f(vector.x / mag, vector.y / mag);
		//printf("NORMALIZED: (%f,%f)\n", normVector.x, normVector.y);
		return normVector;
	}
	else
		return sf::Vector2f(0, 0);
}

void PhysicsObject::CalculateFriction()
{
	float frictionMag = frictionCoeff * normalForce;
	m_friction = m_velocity;
	m_friction = Normalize(m_velocity);
	m_friction *= -1.f;
	m_friction *= frictionMag; 
	//printf("Friction.x:%f\nFriction.y:%f\n", m_friction.x, m_friction.y);
}

sf::FloatRect PhysicsObject::getBBox()
{
	return m_bbox;
}

sf::FloatRect PhysicsObject::getPrevBBox()
{
	return m_prevbbox;
}

sf::Vector2f PhysicsObject::getVelocity()
{
	return m_velocity;
}
