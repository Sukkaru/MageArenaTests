#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager()
{
	//go = &player;
	myvector.push_back(player);
	//myvector.push_back(m_enemy);
}


GameManager::~GameManager()
{
}

void GameManager::Update(sf::RenderWindow * window, sf::Time* dt)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
	for (std::vector<GameObject*>::iterator it = myvector.begin(); it != myvector.end(); ++it)
	{
		printf("In the for loop.\n");
		(*it)->Update(window, dt);
	}
	//m_mage.Update(window,dt);
	//m_enemy.Update(window,dt);
}

void GameManager::Draw(sf::RenderWindow * window)
{
	window->clear();
	for (std::vector<GameObject*>::iterator it = myvector.begin(); it != myvector.end(); ++it)
	{
		//printf("In the for loop.\n");
		(*it)->Draw(window);
	}
	//m_enemy->Draw(window);
	window->display();
}

