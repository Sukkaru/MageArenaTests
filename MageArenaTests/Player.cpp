#include "stdafx.h"
#include "Player.h"


Player::Player(std::vector<std::shared_ptr<GameObject>>* p_vec, std::shared_ptr<CollisionManager> p_collisionmanager)
{
	m_destroyed = false;
	p_gameobjvec = p_vec;
	//Collision stuff
	p_collisionmngr = p_collisionmanager;
	m_collisiongroup = 1;							//Player group is 1
	m_collidablegroups = 12;						//Groups Player can collide with, 2^2 = 4 and 2^3 = 8, terrain and enemy
	//Body stuff
	m_entityheight = 50;
	m_entitywidth = 30;
	m_playersprite.setOrigin(32,39);
	m_playersprite.setPosition(sf::Vector2f(200, 200));
	m_bbox = sf::FloatRect(m_playersprite.getPosition() - sf::Vector2f(m_entitywidth / 2, m_entityheight / 2), sf::Vector2f(m_entitywidth, m_entityheight));
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

	//Sprite stuff
	if (!m_spritesheet.loadFromFile("Graphics/player.png"))
	{
		printf("Error opening player spritesheet file!\n");
	}
	m_playersprite.setTexture(m_spritesheet);
	m_playersprite.setTextureRect(sf::IntRect(256,0,64,64));
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

	m_prevbbox = m_bbox;					//Update the previous bounding box with the current one
	CalculateFriction();
	ApplyForce(m_friction);
	m_velocity += m_accel * dt->asSeconds();
	m_playersprite.setPosition(m_playersprite.getPosition() + m_velocity * dt->asSeconds());
	m_bbox = sf::FloatRect(m_playersprite.getPosition() - sf::Vector2f(m_entitywidth / 2, m_entityheight / 2), sf::Vector2f(m_entitywidth, m_entityheight));
}

void Player::Draw(sf::RenderWindow* window)
{
	window->draw(m_playersprite);
}

void Player::castSpell(sf::RenderWindow* window)
{
	//Calculate mousePos vector in relation to playerPos
	//Cast mousePos from a Vector2I to a Vector2f
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
	sf::Vector2f direction = mousePos - m_playersprite.getPosition();
	//Normalize the direction vector 
	direction = Normalize(direction);
	
	// creates spell. The magic number is how many pixels away from player origin the spell starts
	std::shared_ptr<BaseSpell> _spell = m_currentspell->makeSpell(m_playersprite.getPosition() + (direction * 40.f), direction);
	p_gameobjvec->push_back(_spell);
}

void Player::resolveCollision(std::shared_ptr<PhysicsObject> otherobject, sf::FloatRect collisionrect)
{
	//Player isn't going to do anything on collision for now
}

sf::Vector2f Player::getPosition()
{
	return m_playersprite.getPosition();
}

void Player::setPosition(sf::Vector2f position)
{
	m_playersprite.setPosition(position);
}



