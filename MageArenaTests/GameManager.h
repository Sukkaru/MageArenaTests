#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "CollisionManager.h"
class GameManager
{
public:
	GameManager();
	~GameManager();
	void Update(sf::RenderWindow* window, sf::Time* dt);
	void Draw(sf::RenderWindow* window);
private:
	std::vector<GameObject*> myvector;
	Player p = Player(&myvector);
	Player* player = &p;
	//Player* go = &player;
	//Player* m_mage = Player(&myvector);
	//Enemy* m_enemy = &Enemy(&myvector);
	CollisionManager m_collisionManager;
	
};

