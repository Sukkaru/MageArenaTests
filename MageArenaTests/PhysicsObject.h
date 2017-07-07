#pragma once
#include "GameObject.h"
class PhysicsObject : public GameObject
{
public:
	PhysicsObject();
	~PhysicsObject();
	void virtual			Update(sf::RenderWindow* window, sf::Time* dt);
	void virtual			Draw(sf::RenderWindow* window);
	void					ApplyForce(sf::Vector2f force);
	float					Magnitude(sf::Vector2f vector);
	sf::Vector2f			Normalize(sf::Vector2f vector);
	void					CalculateFriction();
	sf::FloatRect			getBBox();
	sf::FloatRect			getPrevBBox();
	int						getEntityHeight();
	int						getEntityWidth();
	sf::Vector2f			getVelocity();
	void					setVelocity(sf::Vector2f velocity);
	sf::Vector2f virtual	getPosition();
	void virtual			setPosition(sf::Vector2f position);
	int						getCollisionGroup() { return m_collisiongroup; }
	unsigned char			getCollidableGroups() { return m_collidablegroups; }
	int						getCollisionID() { return m_collisionID; }
	void					setCollisionID(int id);


	void virtual			resolveCollision(std::shared_ptr<PhysicsObject> otherobject,sf::FloatRect collisionrect);
protected:
	sf::FloatRect			m_bbox;			//Bounding box for collision detection
	sf::FloatRect			m_prevbbox;		//Previous bounding box for collision detection

	int						m_entityheight;	//Height of the actual entity graphic, because the entity does not take up the entire sprite size
	int						m_entitywidth;	//Width of the actual entity graphic, because the entity does not take up the entire sprite size

	sf::Vector2f			m_upForce;		//For moving up
	sf::Vector2f			m_downForce;	//For moving down
	sf::Vector2f			m_rightForce;	//For moving right
	sf::Vector2f			m_leftForce;	//For moving left

	sf::Vector2f			m_accel;		//Acceleration
	sf::Vector2f			m_velocity;
	float					normalForce;
	float					frictionCoeff;
	sf::Vector2f			m_friction;
	float					m_moveSpeed;
	float					m_maxMoveSpeed;
	float					m_mass;

	int						m_collisiongroup = 0;			//Default: Not part of any collision group
	unsigned char			m_collidablegroups = 0;			//Default: Can't collide with anything
	int						m_collisionID = 0;				//Used to uniquely identify objects during collision detection, gets set by this object, don't overwrite in derived objects
private:
	static int				s_objuniqueID;					//Used to set the collision ID 
};

