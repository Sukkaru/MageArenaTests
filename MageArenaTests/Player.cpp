#include "stdafx.h"
#include "Player.h"


Player::Player(std::vector<std::shared_ptr<GameObject>>* newGameObjects, std::shared_ptr<CollisionManager> collisionManager)
{
	m_destroyed = false;
	m_newGameObjects = newGameObjects;
	//Collision stuff
	m_collisionManager = collisionManager;
	m_collisionGroup = 1;							//Player group is 1
	m_collidableGroups = 12;						//Groups Player can collide with, 2^2 = 4 and 2^3 = 8, terrain and enemy
	//Body stuff
	m_entityHeight = 50;
	m_entityWidth = 30;
	m_playerSprite.setOrigin(32,39);
	m_playerSprite.setPosition(sf::Vector2f(200, 200));
	m_boundingBox = sf::FloatRect(m_playerSprite.getPosition() - sf::Vector2f(m_entityWidth / 2, m_entityHeight / 2), sf::Vector2f(m_entityWidth, m_entityHeight));
	m_previousBoundingBox = m_boundingBox;
	//Initialize physics attributes
	m_moveSpeed =		200;				//Pixels per second
	m_maxMoveSpeed =	1000;				//Pixels per second
	m_mass =			2.0f;  
	m_velocity =		sf::Vector2f(0, 0);
	//Friction variables
	m_normalForce =		100.0f;
	m_frictionCoeff =	5.0f;
	m_friction =		sf::Vector2f(0, 0);
	//Forces used for movement
	m_upForce =			sf::Vector2f(0, -m_moveSpeed);
	m_downForce =		sf::Vector2f(0, m_moveSpeed);
	m_rightForce =		sf::Vector2f(m_moveSpeed, 0);
	m_leftForce =		sf::Vector2f(-m_moveSpeed, 0);

	//Spell stuff
	m_castCooldown =	1.f;
	// initiall setting of a fireball, setting it off screen so that you can't see it. Yes... I know
	m_currentSpell.reset(new Fireball(sf::Vector2f(-100,-100), sf::Vector2f(-100,-100)));

	//Sprite stuff
	if (!m_spriteSheet.loadFromFile("Graphics/player.png"))
	{
		printf("Error opening player spritesheet file!\n");
	}
	m_playerSprite.setTexture(m_spriteSheet);
	//m_playersprite.setTextureRect(sf::IntRect(256,0,64,64));
	m_playerWalkAnimation.reset(new Animation(&m_spriteSheet, sf::Vector2u(64, 64), 0.2f));
}


Player::~Player()
{
}

void Player::update(sf::RenderWindow* window, sf::Time* dt)
{
	//Reset acceleration so it doesn't add on itself
	m_accel = sf::Vector2f(0, 0);
	m_velocity = sf::Vector2f(0, 0);
	//Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))	//Down
	{
		//ApplyForce(m_downForce);
		m_velocity = sf::Vector2f(m_velocity.x,m_moveSpeed);
		m_playerWalkAnimation->update(dt->asSeconds(), 6, 9);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))	//Up
	{
		//ApplyForce(m_upForce);
		m_velocity = sf::Vector2f(m_velocity.x, -m_moveSpeed);
		m_playerWalkAnimation->update(dt->asSeconds(), 4, 9);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	//Left
	{
		//ApplyForce(m_leftForce);
		m_velocity = sf::Vector2f(-m_moveSpeed, m_velocity.y);
		m_playerWalkAnimation->update(dt->asSeconds(), 5, 9);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))	//Right
	{
		//ApplyForce(m_rightForce);
		m_velocity = sf::Vector2f(m_moveSpeed, m_velocity.y);
		m_playerWalkAnimation->update(dt->asSeconds(), 7, 9);
	}
	//Switching Spells
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_currentSpell.reset(new Fireball(sf::Vector2f(-100, -100), sf::Vector2f(-100, -100)));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_currentSpell.reset(new Waterhose(sf::Vector2f(-100, -100), sf::Vector2f(-100, -100)));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		m_currentSpell.reset(new RockSlide(sf::Vector2f(-1000, -1000), sf::Vector2f(-1000, -1000)));
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		
		if (m_currentSpell->getCurrentCastCooldown() > m_currentSpell->getSpellCooldown())
		{
			castSpell(window);
			m_currentSpell->resetCastCooldown();
		}
	}
	m_currentSpell->increaseCastCooldown(dt->asSeconds());

	m_previousBoundingBox = m_boundingBox;					//Update the previous bounding box with the current one
	//CalculateFriction();
	//ApplyForce(m_friction);
	//m_velocity += m_accel * dt->asSeconds();
	m_playerSprite.setPosition(m_playerSprite.getPosition() + m_velocity * dt->asSeconds());
	window->setView(sf::View(m_playerSprite.getPosition(), sf::Vector2f(window->getSize())));
	m_boundingBox = sf::FloatRect(m_playerSprite.getPosition() - sf::Vector2f(m_entityWidth / 2, m_entityHeight / 2), sf::Vector2f(m_entityWidth, m_entityHeight));

	
	m_playerSprite.setTextureRect(m_playerWalkAnimation->getTextureRect());
}

void Player::draw(sf::RenderWindow* window)
{
	window->draw(m_playerSprite);
}

void Player::castSpell(sf::RenderWindow* window)
{
	//Calculate mousePos vector in relation to playerPos
	//Cast mousePos from a Vector2I to a Vector2f
	sf::Vector2f mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	sf::Vector2f mouseDirection = mousePosition - m_playerSprite.getPosition();
	//Normalize the direction vector 
	mouseDirection = normalize(mouseDirection);
	// creates spell. The magic number is how many pixels away from player origin the spell starts
	std::shared_ptr<BaseSpell> spell = m_currentSpell->makeSpell(m_playerSprite.getPosition() + (mouseDirection * 40.f), mouseDirection);
	m_newGameObjects->push_back(spell);
}

void Player::resolveCollision(std::shared_ptr<PhysicsObject> otherObject, sf::FloatRect collisionRect)
{
	//Player isn't going to do anything on collision for now
}

sf::Vector2f Player::getPosition()
{
	return m_playerSprite.getPosition();
}

void Player::setPosition(sf::Vector2f position)
{
	m_playerSprite.setPosition(position);
}



