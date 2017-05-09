#include "stdafx.h"
#include "Player.h"


Player::Player(std::vector<std::shared_ptr<GameObject>>* p_vec/*, std::shared_ptr<CollisionManager> p_collisionptr*/)
{
	myvec = p_vec;
	m_bbox.setSize(sf::Vector2f(50, 50));
	m_bbox.setOrigin(m_bbox.getSize().x / 2, m_bbox.getSize().y / 2);
	m_bbox.setFillColor(sf::Color::Red);
	m_bbox.setPosition(sf::Vector2f(100, 100));
	//m_playerBody.setSize(sf::Vector2f(50, 50));
	//m_playerBody.setFillColor(sf::Color::Red);
	m_aimer.setFillColor(sf::Color::Blue);
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

	//This add the player to the collision grid (sort of)
	//Also prints out where the player is
	//p_collisionptr->addToGrid(std::shared_ptr<Player>(this));
}


Player::~Player()
{
}

void Player::Update(sf::RenderWindow* window, sf::Time* dt)
{
	//sf::Time dt = clock->restart();
	//printf("DT in Player: %f\n", dt->asSeconds());
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
	m_bbox.setPosition(m_bbox.getPosition() + m_velocity * dt->asSeconds());
	//m_playerBody.setPosition(m_playerBody.getPosition() + m_velocity * dt->asSeconds());
	//printf("Position.x:%f\nPosition.y:%f\n", m_playerBody.getPosition().x, m_playerBody.getPosition().y);
}

void Player::Draw(sf::RenderWindow* window)
{
	window->draw(m_bbox);
}

void Player::castSpell(sf::RenderWindow* window)
{
	//Calculate mousePos vector in relation to playerPos
	//Cast mousePos from a Vector2I to a Vector2f
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
	sf::Vector2f direction = mousePos - m_bbox.getPosition();
	//Normalize the direction vector 
	direction = Normalize(direction);
	
	// creates spell. The magic number is how many pixels away from player origin the spell starts
	std::shared_ptr<BaseSpell> _spell = m_currentspell->makeSpell(m_bbox.getPosition() + (direction * 40.f), direction);
	myvec->push_back(_spell);
}


