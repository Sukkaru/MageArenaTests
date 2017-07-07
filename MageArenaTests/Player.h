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
	void virtual								resolveCollision(std::shared_ptr<PhysicsObject> otherobject, sf::FloatRect collisionrect);
	sf::Vector2f								getPosition();
	void										setPosition(sf::Vector2f position);
	int											getPlayerHeight();
	int											getPlayerWidth();
private:
	sf::RectangleShape							m_playerbody;
	std::vector<std::shared_ptr<GameObject>>*	p_gameobjvec;
	std::shared_ptr<CollisionManager>			p_collisionmngr;
	float										m_castcooldown;
	std::shared_ptr<BaseSpell>					m_currentspell;

	sf::Texture									m_spritesheet;
	sf::Sprite									m_playersprite;
	int											m_playerheight;				//Height of player in pixels, this is different from the sprite height
	int											m_playerwidth;				//Width of player in pixels, this is different from the sprite width

};

