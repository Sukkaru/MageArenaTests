#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager()
{
	m_player.reset(new Player(&addvector));
	m_testdummy.reset(new Enemy(&addvector)); //For testing
	addvector.push_back(m_player);
	addvector.push_back(m_testdummy);
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
		//if (event.type == sf::Event::MouseButtonPressed)
		//{
			//if (event.mouseButton.button == sf::Mouse::Left)
			//{

				//m_player->castSpell(window);
			//}
		//}
	}

	if (addvector.size() > 0)
	{
		for (auto & value : addvector)
		{
			myvector.push_back(value);
		}
		addvector.clear();
	}

	for (auto & value : myvector)
	{
		value->Update(window,dt);
	}
}

void GameManager::Draw(sf::RenderWindow * window)
{
	window->clear();
	for (auto & value : myvector)
	{
		value->Draw(window);
	}
	window->display();
}
