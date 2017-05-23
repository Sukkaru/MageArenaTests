#include "stdafx.h"
#include "Player.h"


Player::Player(std::vector<std::shared_ptr<GameObject>>* p_vec, std::shared_ptr<CollisionManager> p_collisionmanager)
{
	m_destroyed = false;
	p_gameobjvec = p_vec;
	//Collision stuff
	p_collisionmngr = p_collisionmanager;
	collisiongroup = 1;						//Player group is 1
	collidablegroups = 6;					//Groups Player can collide with, 2 and 4, terrain and enemy
	//Body stuff
	m_playerbody.setSize(sf::Vector2f(50, 50));
	m_playerbody.setOrigin(m_playerbody.getSize().x / 2, m_playerbody.getSize().y / 2);
	m_playerbody.setFillColor(sf::Color::Red);
	m_playerbody.setPosition(sf::Vector2f(100, 100));
	m_bbox = m_playerbody.getGlobalBounds();
	m_prevbbox = m_bbox;
	//Initialize physics attributes
	m_moveSpeed =		1000;				//Pixels per second
	m_maxMoveSpeed =	1000;				//Pixels per second
	m_mass =			2.0f;  
	m_velocity =		sf::Vector2f(0, 0);
	//Friction variables
	normalForce =		100.0f;
	frictionCoeff =		5.0f;
	m_friction =		sf::Vector2f(0, 0);
	//Forces used for movement
	m_upForce =			sf::Vector2f(0, -m_moveSpeed);
	m_downForce =		sf::Vector2f(0, m_moveSpeed);
	m_rightForce =		sf::Vector2f(m_moveSpeed, 0);
	m_leftForce =		sf::Vector2f(-m_moveSpeed, 0);

	//Spell stuff
	m_castcooldown =	1.f;
	// initiall setting of a fireball, setting it off screen so that you can't see it. Yes... I know
	m_currentspell.reset(new Fireball(sf::Vector2f(-100,-100), sf::Vector2f(-100,-100)));
}


Player::~Player()
{
}

void Player::Update(sf::RenderWindow* window, sf::Time* dt)
{
	//Reset acceleration so it doesn't add on itself
	m_accel = sf::Vector2f(0, 0);
	//Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))	//Down
	{
		ApplyForce(m_downForce);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))	//Up
	{
		ApplyForce(m_upForce);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	//Left
	{
		ApplyForce(m_leftForce);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))	//Right
	{
		ApplyForce(m_rightForce);
	}
	//Switching Spells
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_currentspell.reset(new Fireball(sf::Vector2f(-100, -100), sf::Vector2f(-100, -100)));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_currentspell.reset(new Waterhose(sf::Vector2f(-100, -100), sf::Vector2f(-100, -100)));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		m_currentspell.reset(new RockSlide(sf::Vector2f(-1000, -1000), sf::Vector2f(-1000, -1000)));
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		
		if (m_currentspell->getCurrentCastCooldown() > m_currentspell->getSpellCooldown())
		{
			castSpell(window);
			m_currentspell->resetCastCooldown();
		}
	}
	m_currentspell->increaseCastCooldown(dt->asSeconds());

	CalculateFriction();
	ApplyForce(m_friction);
	m_velocity += m_accel * dt->asSeconds();
	//printf("Accel.x:%f\nAccel.y:%f\n", m_accel.x, m_accel.y);
	//printf("Velocity.x:%f\nVelocity.y:%f\n", m_velocity.x, m_velocity.y);
	m_prevbbox = m_bbox;															//Update the previous bounding box with the current one
	m_playerbody.setPosition(m_playerbody.getPosition() + m_velocity * dt->asSeconds());
	m_bbox = m_playerbody.getGlobalBounds();										//Update the current bounding box
	//printf("Position.x:%f\nPosition.y:%f\n", m_playerBody.getPosition().x, m_playerBody.getPosition().y);
}

void Player::Draw(sf::RenderWindow* window)
{
	window->draw(m_playerbody);
}

void Player::castSpell(sf::RenderWindow* window)
{
	//Calculate mousePos vector in relation to playerPos
	//Cast mousePos from a Vector2I to a Vector2f
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
	sf::Vector2f direction = mousePos - m_playerbody.getPosition();
	//Normalize the direction vector 
	direction = Normalize(direction);
	
	// creates spell. The magic number is how many pixels away from player origin the spell starts
	std::shared_ptr<BaseSpell> _spell = m_currentspell->makeSpell(m_playerbody.getPosition() + (direction * 40.f), direction);
	p_gameobjvec->push_back(_spell);
}


