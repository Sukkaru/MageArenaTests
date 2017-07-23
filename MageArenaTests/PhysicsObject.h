#pragma once
#include "GameObject.h"
class PhysicsObject : public GameObject
{
public:
	PhysicsObject();
	~PhysicsObject();
	void virtual			update(sf::RenderWindow* window, sf::Time* dt);
	void virtual			draw(sf::RenderWindow* window);
	void					applyForce(sf::Vector2f force);
	float					magnitude(sf::Vector2f vector);
	sf::Vector2f			normalize(sf::Vector2f vector);
	void					calculateFriction();
	sf::FloatRect			getBoundingBox();
	sf::FloatRect			getPreviousBoundingBox();
	int						getEntityHeight();
	int						getEntityWidth();
	sf::Vector2f			getVelocity();
	void					setVelocity(sf::Vector2f velocity);
	sf::Vector2f virtual	getPosition();
	void virtual			setPosition(sf::Vector2f position);
	int						getCollisionGroup();
	unsigned char			getCollidableGroups();
	int						getCollisionID();
	void					setCollisionID(int id);


	void virtual			resolveCollision(std::shared_ptr<PhysicsObject> otherObject,sf::FloatRect collisionRect);
protected:
	sf::FloatRect			m_boundingBox;			//Bounding box for collision detection
	sf::FloatRect			m_previousBoundingBox;		//Previous bounding box for collision detection

	int						m_entityHeight;	//Height of the actual entity graphic, because the entity does not take up the entire sprite size
	int						m_entityWidth;	//Width of the actual entity graphic, because the entity does not take up the entire sprite size

	sf::Vector2f			m_upForce;		//For moving up
	sf::Vector2f			m_downForce;	//For moving down
	sf::Vector2f			m_rightForce;	//For moving right
	sf::Vector2f			m_leftForce;	//For moving left

	sf::Vector2f			m_accel;		//Acceleration
	sf::Vector2f			m_velocity;
	float					m_normalForce;
	float					m_frictionCoeff;
	sf::Vector2f			m_friction;
	float					m_moveSpeed;
	float					m_maxMoveSpeed;
	float					m_mass;

	int						m_collisionGroup;			//Default: Not part of any collision group
	unsigned char			m_collidableGroups;			//Default: Can't collide with anything
	int						m_collisionID;				//Used to uniquely identify objects during collision detection, gets set by this object, don't overwrite in derived objects
private:
	static int				s_objUniqueID;				//Used to set the collision ID 
};

