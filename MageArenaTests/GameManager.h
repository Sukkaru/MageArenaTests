#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "Arena.h"
class GameManager
{
public:
	GameManager(sf::RenderWindow* window);
	~GameManager();
	void update(sf::RenderWindow* window, sf::Time* dt);
	void draw(sf::RenderWindow* window);
private:
	std::vector<std::shared_ptr<GameObject>> m_gameObjects;
	std::vector<std::shared_ptr<GameObject>> m_newGameObjects;
	std::shared_ptr<CollisionManager> m_collisionManager;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<Enemy> m_testDummy;
	std::shared_ptr<Arena> m_arena;
	
	int m_arenaWidth;
	int m_arenaHeight;
};

