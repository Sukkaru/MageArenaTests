#include "stdafx.h"
#include "PhysicsObject.h"

int PhysicsObject::s_objUniqueID = 0;

PhysicsObject::PhysicsObject()
{
	++s_objUniqueID;
	m_collisionID = s_objUniqueID;
	m_collisionGroup = 0;			//Default: Not part of any collision group
	m_collidableGroups = 0;      	//Default: Can't collide with anything
}


PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::update(sf::RenderWindow * window, sf::Time* dt)
{
}

void PhysicsObject::draw(sf::RenderWindow * window)
{
}

void PhysicsObject::applyForce(sf::Vector2f force)
{
	//Scaling the vector down by the mass
	force /= m_mass;
	m_accel += force;
}

float PhysicsObject::magnitude(sf::Vector2f vector)
{
	//Raising to the power of .5f is the same as taking the square root
	float temp = powf((vector.x * vector.x) + (vector.y * vector.y),0.5f);
	//printf("Magnitude: %f\n", temp);
	return temp;
}

sf::Vector2f PhysicsObject::normalize(sf::Vector2f vector)
{
	float mag = magnitude(vector);
	if (mag > 0.0)
	{
		sf::Vector2f normVector = sf::Vector2f(vector.x / mag, vector.y / mag);
		//printf("NORMALIZED: (%f,%f)\n", normVector.x, normVector.y);
		return normVector;
	}
	else
		return sf::Vector2f(0, 0);
}

void PhysicsObject::calculateFriction()
{
	float frictionMag = m_frictionCoeff * m_normalForce;
	m_friction = normalize(m_velocity);
	m_friction *= -1.f;
	m_friction *= frictionMag; 
	//printf("Friction.x:%f\nFriction.y:%f\n", m_friction.x, m_friction.y);
}

sf::FloatRect PhysicsObject::getBoundingBox()
{
	return m_boundingBox;
}

sf::FloatRect PhysicsObject::getPreviousBoundingBox()
{
	return m_previousBoundingBox;
}

int PhysicsObject::getEntityHeight()
{
	return m_entityHeight;
}

int PhysicsObject::getEntityWidth()
{
	return m_entityWidth;
}

sf::Vector2f PhysicsObject::getVelocity()
{
	return m_velocity;
}

void PhysicsObject::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

sf::Vector2f PhysicsObject::getPosition()
{
	return sf::Vector2f();
}

void PhysicsObject::setPosition(sf::Vector2f position)
{
}

int PhysicsObject::getCollisionGroup()
{
	return m_collisionGroup;
}

unsigned char PhysicsObject::getCollidableGroups()
{
	return m_collidableGroups;
}

int PhysicsObject::getCollisionID()
{
	return m_collisionID;
}

void PhysicsObject::setCollisionID(int id)
{
	m_collisionID = id;
}

void PhysicsObject::resolveCollision(std::shared_ptr<PhysicsObject> otherObject, sf::FloatRect collisionRect)
{

}
