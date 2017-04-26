#pragma once
#include "PhysicsObject.h"
#include "Fireball.h"
#include <SFML/Graphics.hpp>
class Player : public PhysicsObject
{
public:
	Player(std::vector<std::shared_ptr<GameObject>>* p_vec);
	~Player();
	void virtual			Update(sf::RenderWindow* window, sf::Time* dt);
	void virtual			Draw(sf::RenderWindow* window);
	void					castSpell(sf::RenderWindow* window);
	
private:
	sf::RectangleShape							m_playerBody;
	sf::RectangleShape							m_aimer;		//For player aiming, points toward mouse position
	std::vector<std::shared_ptr<GameObject>>*	myvec;

};

