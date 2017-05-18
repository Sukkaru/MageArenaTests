#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager(sf::RenderWindow* window)
{	
	p_colptr.reset(new CollisionManager(window));
	//Keep these above anything that uses them
	m_testdummy.reset(new Enemy(&addvector)); //For testing
	m_player.reset(new Player(&addvector, p_colptr));
	//Add player and testdummy to the collision manager
	p_colptr->addToGrid(m_player,m_player->getBBox().getGlobalBounds());
	p_colptr->addToGrid(m_testdummy,m_testdummy->getBBox().getGlobalBounds());
	

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
	}
	//Press ESC to close the game window
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


	for (auto i = 0; i < myvector.size(); i++)
	{
		//Check if the current object is a PhysicsObject
		if (std::shared_ptr<PhysicsObject> p = std::dynamic_pointer_cast<PhysicsObject>(myvector[i]))
		{
			//If the object is moving, update its position in the collision grid
			if (p->getVelocity().x != 0 || p->getVelocity().y != 0)
			{
				p_colptr->updateGrid(p,p->getBBox().getGlobalBounds(),p->getPrevBBox().getGlobalBounds());
			}
			
		}
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
