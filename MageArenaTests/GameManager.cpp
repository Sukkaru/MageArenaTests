#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager()
{
	//go = &player;
	player.reset(new Player(&addvector));
	addvector.push_back(player);
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
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{

				player->castSpell(window);
			}
		}
	}

	if (addvector.size() > 0)
	{
		for (auto & value : addvector)
		{
			myvector.push_back(value);
			value->Update(window, dt);
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
	//m_enemy->Draw(window);
	window->display();
}
