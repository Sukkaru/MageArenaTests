#include "stdafx.h"
#include "CollisionManager.h"


CollisionManager::CollisionManager(sf::RenderWindow* window)
{
	//Determine how many boxes needed
	//Add one to account for possible rounding down
	numboxeswide = (window->getSize().x / BOX_WIDTH) + 1;
	numboxeshigh = (window->getSize().y / BOX_HEIGHT) + 1;
	printf("High:%d \n Wide:%d \n", numboxeshigh, numboxeswide);
	//Make sure the grid has allocated enough space for all boxes
	grid.reserve(numboxeswide);
	printf("Grid capacity:%d \n", grid.capacity());

	for (int i = 0; i < numboxeswide; i++)
	{
		
		//printf("Value capacity:%d \n", grid.at(i).capacity());
	}
	/*for (auto& value : grid)
	{
		value.reserve(numboxeshigh);
		printf("Value capacity:%d \n", value.capacity());
	}*/
	printf("cap:%d\n", grid.empty());
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::checkCollisions()
{
}

void CollisionManager::addToGrid(std::shared_ptr<PhysicsObject> obj)
{
	//This function takes an object, gets the position of the object
	//and adds the object to the vector of the grid squares that it is in
	//For now this will only work for normal sized objects, I'll add code for bigger things later
	
	//Compute what box to put the object in
	//obj.pos.x/BOX_WIDTH = horizontal box number
	int horizbox = obj->getBBox().getPosition().x / BOX_WIDTH;
	

}

void CollisionManager::delFromGrid(sf::Vector2f pos)
{
}
