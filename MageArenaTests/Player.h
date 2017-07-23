 #pragma once
#include "PhysicsObject.h"
#include "Fireball.h"
#include "Waterhose.h"
#include "RockSlide.h"
#include "CollisionManager.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class Player : public PhysicsObject
{
public:
	Player(std::vector<std::shared_ptr<GameObject>>* newGameObjects,std::shared_ptr<CollisionManager> collisionManager);
	~Player();
	void virtual								update(sf::RenderWindow* window, sf::Time* dt);
	void virtual								draw(sf::RenderWindow* window);
	void										castSpell(sf::RenderWindow* window);
	void virtual								resolveCollision(std::shared_ptr<PhysicsObject> otherObject, sf::FloatRect collisionRect);
	sf::Vector2f								getPosition();
	void										setPosition(sf::Vector2f position);
private:
	std::vector<std::shared_ptr<GameObject>>*	m_newGameObjects;
	std::shared_ptr<CollisionManager>			m_collisionManager;
	float										m_castCooldown;
	std::shared_ptr<BaseSpell>					m_currentSpell;

	sf::Texture									m_spriteSheet;
	sf::Sprite									m_playerSprite;
	std::unique_ptr<Animation>					m_playerWalkAnimation;
};

