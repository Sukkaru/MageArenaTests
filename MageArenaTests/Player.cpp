#include "stdafx.h"
#include "Player.h"


Player::Player(std::vector<std::unique_ptr<GameObject>>* p_vec)
{
	myvec = p_vec;
	m_playerBody.setSize(sf::Vector2f(50, 50));
	m_playerBody.setFillColor(sf::Color::Red);
	m_aimer.setFillColor(sf::Color::Blue);
	//Initialize physics attributes
	m_moveSpeed = 1000;				//Pixels per second
	m_maxMoveSpeed = 1000;			//Pixels per second
	m_mass = 2.0f;  
	m_velocity = sf::Vector2f(0, 0);
	//Friction variables
	normalForce = 1.0f;
	frictionCoeff = 5.0f;
	m_friction = sf::Vector2f(0, 0);
	//Forces used for movement
	m_upForce = sf::Vector2f(0, -m_moveSpeed);
	m_downForce = sf::Vector2f(0, m_moveSpeed);
	m_rightForce = sf::Vector2f(m_moveSpeed, 0);
	m_leftForce = sf::Vector2f(-m_moveSpeed, 0);

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
	CalculateFriction();
	ApplyForce(m_friction);
	m_velocity += m_accel * dt->asSeconds();
	//printf("Accel.x:%f\nAccel.y:%f\n", m_accel.x, m_accel.y);
	//printf("Velocity.x:%f\nVelocity.y:%f\n", m_velocity.x, m_velocity.y);
	m_playerBody.setPosition(m_playerBody.getPosition() + m_velocity * dt->asSeconds());
	//printf("Position.x:%f\nPosition.y:%f\n", m_playerBody.getPosition().x, m_playerBody.getPosition().y);
}

void Player::Draw(sf::RenderWindow* window)
{
	window->draw(m_playerBody);
}

void Player::castSpell(sf::RenderWindow* window)
{
	//Calculate mousePos vector in relation to playerPos
	//Cast mousePos from a Vector2I to a Vector2f
	printf("Left Mouse Pressed\n");
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
	sf::Vector2f direction = mousePos - m_playerBody.getPosition();
	//Normalize the direction vector 
	direction = Normalize(direction);
	//Create the Fireball 
	//Fireball fireball(direction);
	std::unique_ptr<GameObject> fball(new Fireball(direction));
	printf("Fireball address: %x\n", fball);
	//printf("myvec size in player: %d", myvec->size());
	myvec->push_back(fball);
}



