#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager()
{
	
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

	m_mage.Update(window,dt);
	m_enemy.Update(window,dt);
}

void GameManager::Draw(sf::RenderWindow * window)
{
	window->clear();
	m_mage.Draw(window);
	m_enemy.Draw(window);
	window->display();
}

