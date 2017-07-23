#include "stdafx.h"
#include "CollisionManager.h"


CollisionManager::CollisionManager(int arenaWidth, int arenaHeight)
{
	//Determine how many boxes needed
	//Add one to account for possible rounding down
	m_nBoxesWide = (arenaWidth / BOX_WIDTH) + 1;
	m_nBoxesHigh = (arenaHeight / BOX_HEIGHT) + 1;
	//printf("High:%d \n Wide:%d \n", numboxeshigh, numboxeswide);
	//Make sure the grid has allocated enough space for all boxes
	m_grid = std::vector<std::vector<std::vector<std::shared_ptr<PhysicsObject>>>>(m_nBoxesHigh, std::vector<std::vector<std::shared_ptr<PhysicsObject>>>(m_nBoxesWide, std::vector<std::shared_ptr<PhysicsObject>>()));
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::checkCollisions()
{
	//Empty the set of collision pairs
	m_collisionPairs.clear();
	//Just iterating through the entire grid for now
	//If this is too slow it can be optimized
	//displayGrid();
	for (int row = 0; row < m_grid.size(); row++)
	{
		for (int col = 0; col < m_grid[row].size(); col++)
		{
			for (int obj = 0; obj < m_grid[row][col].size(); obj++)
			{
				for (int obj2 = obj + 1; obj2 < m_grid[row][col].size(); obj2++)
				{
					//Compare stuff here
					//If obj can collide with obj2's group
					if (checkCollisionGroup(m_grid[row][col][obj]->getCollidableGroups(), m_grid[row][col][obj2]->getCollisionGroup()) == true)
					{
						//If this object pair has not been checked for collisions yet
						if (m_collisionPairs.count(m_grid[row][col][obj]->getCollisionID() + ":" + m_grid[row][col][obj2]->getCollisionID()) == 0)
						{
							sf::FloatRect collisionRect = createCollisionRect(m_grid[row][col][obj]->getBoundingBox(), m_grid[row][col][obj2]->getBoundingBox());
							//Check if there is an actual collision
							if (checkRectForCollision(collisionRect) == true)
							{
								//printf("Collision!\n");
								m_grid[row][col][obj]->resolveCollision(m_grid[row][col][obj2], collisionRect);
								m_grid[row][col][obj2]->resolveCollision(m_grid[row][col][obj], collisionRect);
								//Add the pair of objects to the collision pair set
								//This prevents the objects from being checked for collision more than once
								m_collisionPairs.insert(m_grid[row][col][obj]->getCollisionID() + ":" + m_grid[row][col][obj2]->getCollisionID());
							}
						}
					}
				}
			}
		}
	}
}

void CollisionManager::addToGrid(std::shared_ptr<PhysicsObject> obj, sf::FloatRect boundingRect)
{
	//This function takes an object, gets the position of the object
	//and adds the object to the vector of the grid squares that it is in
	
	//Get the four corners of the global bounding rectangle of the object
	float objLeft = boundingRect.left;
	float objTop = boundingRect.top;
	float objRight = objLeft + boundingRect.width;
	float objBot = objTop + boundingRect.height;
	//printf("Object left,top,right,bot: %f,%f,%f,%f\n", objleft, objtop, objright, objbot);
	//Compute the rows and columns that correspond to the corners of the rectangle
	int startColumn = objLeft / BOX_WIDTH;
	int endColumn = objRight / BOX_WIDTH;
	int startRow = objTop / BOX_HEIGHT;
	int endRow = objBot / BOX_HEIGHT;
	//Go through every box in between the starting and ending column and row
	for (int row = startRow; row <= endRow; row++)
	{
		if (row > -1 && row < m_nBoxesHigh)
		{
			for (int col = startColumn; col <= endColumn; col++)
			{
				if (col > -1 && col < m_nBoxesWide)
				{
					m_grid[row][col].push_back(obj);	//Add the object pointer to the box
				}
			}
		}
	}
	
	//displayGrid();
}

void CollisionManager::delFromGrid(std::shared_ptr<PhysicsObject> obj, sf::FloatRect boundingRect)
{
	//This function deletes all pointers to an object from all grid boxes it is in

	//Get the four corners of the global bounding rectangle of the object
	float objLeft = boundingRect.left;
	float objTop = boundingRect.top;
	float objRight = objLeft + boundingRect.width;
	float objBot = objTop + boundingRect.height;
	//printf("Object left,top,right,bot: %f,%f,%f,%f\n", objleft, objtop, objright, objbot);
	//Compute the rows and columns that correspond to the corners of the rectangle
	int startColumn = objLeft / BOX_WIDTH;
	int endColumn = objRight / BOX_WIDTH;
	int startRow = objTop / BOX_HEIGHT;
	int endRow = objBot / BOX_HEIGHT;
	//Go through every box in between the starting and ending column and row
	for (int row = startRow; row <= endRow; row++)
	{
		if (row > -1 && row < m_nBoxesHigh)
		{
			for (int col = startColumn; col <= endColumn; col++)
			{
				if (col > -1 && col < m_nBoxesWide)
				{
					//Search the vector of object pointers at the specific box
					for (auto it = m_grid[row][col].begin(); it != m_grid[row][col].end();)
					{
						if (*it == obj)		//If the object pointer is in the vector
						{
							it = m_grid[row][col].erase(it);	//Erase the object pointer from the vector
						}
						else
							++it;
					}
				}
			}
		}
	}
	
	//displayGrid();
}

void CollisionManager::updateGrid(std::shared_ptr<PhysicsObject> obj, sf::FloatRect boundingRect, sf::FloatRect previousBoundingRect)
{
	//First delete the object from the grid
	delFromGrid(obj,previousBoundingRect);
	//Then add it back in to the grid
	addToGrid(obj,boundingRect);
}

void CollisionManager::displayGrid()
{
	//Iterates through the entire grid printing out the amount of objects in each box
	for (int i = 0; i < m_grid.size(); i++)
	{
		for (int j = 0; j < m_grid[i].size(); j++)
		{
			printf("[%d]", m_grid[i][j].size());
		}
		printf("\n");
	}
	printf("\n");
}

bool CollisionManager::checkCollisionGroup(unsigned char collidableGroups, int collisionGroup)
{
	unsigned char mask = 1;							//Initialize the bitmask
	mask = mask << collisionGroup;					//Shift the active bit over to the slot that corresponds to the collision group
	return (collidableGroups & mask) > 0;			//If there is a 1 in the slot that corresponds to that group, the objects can collide
}

sf::FloatRect CollisionManager::createCollisionRect(sf::FloatRect obj1BoundingBox, sf::FloatRect obj2BoundingBox)
{
	float obj1Left = obj1BoundingBox.left;
	float obj1Top = obj1BoundingBox.top;
	float obj1Right = obj1BoundingBox.left + obj1BoundingBox.width;
	float obj1Bot = obj1BoundingBox.top + obj1BoundingBox.height;

	float obj2Left = obj2BoundingBox.left;
	float obj2Top = obj2BoundingBox.top;
	float obj2Right = obj2BoundingBox.left + obj2BoundingBox.width;
	float obj2Bot = obj2BoundingBox.top + obj2BoundingBox.height;
	//Create the collision rectangle
	float rectLeft = std::max(obj1Left, obj2Left);
	float rectTop = std::max(obj1Top, obj2Top);
	float rectRight = std::min(obj1Right, obj2Right);
	float rectBot = std::min(obj1Bot, obj2Bot);

	sf::FloatRect collisionRect = sf::FloatRect(rectLeft, rectTop, rectRight - rectLeft, rectBot - rectTop);
	return collisionRect;
}

bool CollisionManager::checkRectForCollision(sf::FloatRect collisionRect)
{
	return collisionRect.left < (collisionRect.left + collisionRect.width) && collisionRect.top < (collisionRect.top + collisionRect.height);
}
