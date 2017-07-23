#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager(sf::RenderWindow* window)
{	

	m_arenaWidth = 1280;		//Must be multiple of 64
	m_arenaHeight = 768;		//Must be multiple of 64
	m_collisionManager.reset(new CollisionManager(m_arenaWidth,m_arenaHeight));
	//Keep these above anything that uses them
	m_testDummy.reset(new Enemy(&m_newGameObjects)); //For testing
	m_player.reset(new Player(&m_newGameObjects, m_collisionManager));
	//Add player and testdummy to the collision manager
	m_collisionManager->addToGrid(m_player,m_player->getBoundingBox());
	m_collisionManager->addToGrid(m_testDummy,m_testDummy->getBoundingBox());
	
	m_arena.reset(new Arena(m_collisionManager, m_arenaWidth, m_arenaHeight));

	//Add player and testdummy to the GameObject vector	
	m_newGameObjects.push_back(m_player);
	m_newGameObjects.push_back(m_testDummy);
}


GameManager::~GameManager()
{
}

void GameManager::update(sf::RenderWindow * window, sf::Time* dt)
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

	//Moves any new game objects into the game object vector, 
	//this is done to prevent the game object vector iterator from becoming invalid 
	if (m_newGameObjects.size() > 0)
	{
		for (auto & value : m_newGameObjects)
		{
			m_gameObjects.push_back(value);
		}
		m_newGameObjects.clear();
	}


	for (auto i = 0; i < m_gameObjects.size(); i++)
	{
		//Check if the current object is a PhysicsObject
		if (std::shared_ptr<PhysicsObject> physicsObject = std::dynamic_pointer_cast<PhysicsObject>(m_gameObjects[i]))
		{
			//If the object is moving, update its position in the collision grid
			if (physicsObject->getVelocity().x != 0 || physicsObject->getVelocity().y != 0)
			{
				m_collisionManager->updateGrid(physicsObject,physicsObject->getBoundingBox(),physicsObject->getPreviousBoundingBox());
			}
			
		}
		m_collisionManager->checkCollisions();				//Check the collision grid for collisions
		m_gameObjects[i]->update(window, dt);
		//Removes all game objects flagged as destroyed
		if (m_gameObjects[i]->getDestroyed())
		{
			//Remove the object from the collision grid
			if (std::shared_ptr<PhysicsObject> physicsObject = std::dynamic_pointer_cast<PhysicsObject>(m_gameObjects[i]))
			{
				m_collisionManager->delFromGrid(physicsObject, physicsObject->getBoundingBox());
				m_collisionManager->delFromGrid(physicsObject, physicsObject->getPreviousBoundingBox());
			}
			m_gameObjects.erase(m_gameObjects.begin() + i);
			i--;
		}
		
	}
}

void GameManager::draw(sf::RenderWindow * window)
{
	window->clear();
	//Draw arena
	m_arena->draw(window);
	for (auto & value : m_gameObjects)
	{
		value->draw(window);
	}
	window->display();
}
