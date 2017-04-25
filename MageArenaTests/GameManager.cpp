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
	//for (std::vector<GameObject*>::iterator it = myvector.begin(); it != myvector.end(); ++it)
	//{
	//	printf("In the for loop.\n");
	//	(*it)->Update(window, dt);
	//}
	//Check to see if there is anything in the addvector
	//Add it to the normal vector
	//Then iterate over the vector
	if (addvector.size() > 0)
	{
		for (std::vector<std::shared_ptr<GameObject>>::iterator it = addvector.begin(); it != addvector.end(); ++it)
		{
			//printf("Dude: %x", *it);
			myvector.push_back(*it);
			(*it)->Update(window, dt);
			//printf("Dude: %x", *it);
		}
		addvector.clear();
		//printf("Size of addvector: %d\n", addvector.size());
	}
	for (auto & value : myvector)
	{
		value->Update(window,dt);
	}
	//m_mage.Update(window,dt);
	//m_enemy.Update(window,dt);
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

