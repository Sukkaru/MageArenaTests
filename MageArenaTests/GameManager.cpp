#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager(sf::RenderWindow* window)
{
	//CollisionManager m_collisionmanager(window);
	std::shared_ptr<CollisionManager> p_colptr;
	p_colptr.reset(new CollisionManager(window));
	m_player.reset(new Player(&addvector,p_colptr));
	m_testdummy.reset(new Enemy(&addvector)); //For testing
	//Add player and testdummy to the collision manager
	p_colptr->addToGrid(m_player);
	p_colptr->delFromGrid(m_player);
	p_colptr->addToGrid(m_testdummy);
	//Add player and testdummy to the GameObject vector
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window->close();
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
