 #pragma once
#include "PhysicsObject.h"
#include "Fireball.h"
#include "Waterhose.h"
#include "RockSlide.h"
#include "CollisionManager.h"
#include <SFML/Graphics.hpp>

class Player : public PhysicsObject
{
public:
	Player(std::vector<std::shared_ptr<GameObject>>* p_vec,std::shared_ptr<CollisionManager> p_collisionmanager);
	~Player();
	void virtual								Update(sf::RenderWindow* window, sf::Time* dt);
	void virtual								Draw(sf::RenderWindow* window);
	void										castSpell(sf::RenderWindow* window);
	
private:
	sf::RectangleShape							m_playerbody;
	std::vector<std::shared_ptr<GameObject>>*	p_gameobjvec;
	std::shared_ptr<CollisionManager>			p_collisionmngr;
	float										m_castcooldown;
	std::shared_ptr<BaseSpell>					m_currentspell;
};

