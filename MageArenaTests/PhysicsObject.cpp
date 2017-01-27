#include "stdafx.h"
#include "PhysicsObject.h"


PhysicsObject::PhysicsObject()
{
}


PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::ApplyForce(sf::Vector2f force)
{
	//Scaling the vector down by the mass
	force /= m_mass;
	m_accel += force;
}
