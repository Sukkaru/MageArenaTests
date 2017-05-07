#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager(sf::RenderWindow* window)
{
	/*
	
	** Commented out until finished or working
	** also commented out collider arguements in player header and cpp

	//CollisionManager m_collisionmanager(window);
	std::shared_ptr<CollisionManager> p_colptr;
	p_colptr.reset(new CollisionManager(window));
	//Add player and testdummy to the collision manager
	p_colptr->addToGrid(m_player);
	p_colptr->delFromGrid(m_player);
	p_colptr->addToGrid(m_testdummy);
	*/

	//Add player and testdummy to the GameObject vector
	m_testdummy.reset(new Enemy(&addvector)); //For testing
	m_player.reset(new Player(&addvector/*,p_colptr*/));
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

	//for (auto & value : myvector)
	//{
	//	value->Update(window,dt);

	//	// Checks to see if the current value is a base spell, if it is it checks to see if it is flagged destroy
	//	// if it is destroyed, remove from the vector of game objects and back up a step

	//	if (std::dynamic_pointer_cast<BaseSpell>(value))
	//	{
	//		if (value->getDestroyed())
	//		{
	//			
	//		}
	//	}
	//}

	for (auto i = 0; i < myvector.size(); i++)
	{
		myvector[i]->Update(window, dt);

		//removes
		if (myvector[i]->getDestroyed())
		{
			myvector.erase(myvector.begin() + i);
			i--;
		}
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
