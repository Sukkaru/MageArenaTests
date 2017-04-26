#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "CollisionManager.h"
class GameManager
{
public:
	GameManager(sf::RenderWindow* window);
	~GameManager();
	void Update(sf::RenderWindow* window, sf::Time* dt);
	void Draw(sf::RenderWindow* window);
private:
	std::vector<std::shared_ptr<GameObject>> myvector;
	std::vector<std::shared_ptr<GameObject>> addvector;
	std::vector<std::shared_ptr<GameObject>> delvector;	//Might not use this but keeping it for reminder

	std::shared_ptr<Player> m_player;
	std::shared_ptr<Enemy> m_testdummy;
	//CollisionManager m_collisionManager;
	
};

