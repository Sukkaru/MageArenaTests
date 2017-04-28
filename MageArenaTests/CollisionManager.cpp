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
	grid = std::vector<std::vector<std::vector<std::shared_ptr<PhysicsObject>>>>(numboxeswide, std::vector<std::vector<std::shared_ptr<PhysicsObject>>>(numboxeshigh, std::vector<std::shared_ptr<PhysicsObject>>()));
	printf("Capacity of row: %d \n", grid.capacity());
	for (int i = 0; i < numboxeswide; i++)
	{
		printf("Capacity of columns: %d\n", grid[i].capacity());
	}
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
	int rowbox = obj->getBBox().getPosition().x / BOX_WIDTH;
	int colbox = obj->getBBox().getPosition().y / BOX_HEIGHT;
	grid[rowbox][colbox].push_back(obj);
	if(grid[rowbox][colbox].size() > 0)
		printf("I'm in grid: [%d][%d]\n", rowbox, colbox);
	
}

void CollisionManager::delFromGrid(std::shared_ptr<PhysicsObject> obj)
{
	int rowbox = obj->getBBox().getPosition().x / BOX_WIDTH;
	int colbox = obj->getBBox().getPosition().y / BOX_HEIGHT;
	for (auto it = grid[rowbox][colbox].begin(); it != grid[rowbox][colbox].end();)
	{
		if (*it == obj)
		{
			it = grid[rowbox][colbox].erase(it);
			printf("I am no longer in the grid: %d\n", grid[rowbox][colbox].size());
		}
		else
			++it;
	}
}
