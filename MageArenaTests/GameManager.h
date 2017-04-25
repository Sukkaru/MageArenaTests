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
	std::vector<std::shared_ptr<GameObject>> myvector;
	std::vector<std::shared_ptr<GameObject>> addvector;
	std::vector<std::shared_ptr<GameObject>> delvector;

	//Player p = Player(&addvector);		//This will eventually need a delvector reference, but worrying about add only for now
	//Player* player = &p;
	std::shared_ptr<Player> player;
	//Player* go = &player;
	//Player* m_mage = Player(&myvector);
	//Enemy* m_enemy = &Enemy(&myvector);
	CollisionManager m_collisionManager;
	
};

