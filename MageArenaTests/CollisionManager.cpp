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
	
	//Get the four corners of the global bounding rectangle of the object
	float objleft = obj->getBBox().getGlobalBounds().left;
	float objtop = obj->getBBox().getGlobalBounds().top;
	float objright = objleft + obj->getBBox().getGlobalBounds().width;
	float objbot = objtop + obj->getBBox().getGlobalBounds().height;
	printf("Object left,top,right,bot: %f,%f,%f,%f\n", objleft, objtop, objright, objbot);
	//Compute the rows and columns that correspond to the corners of the rectangle
	int startcol = objleft / BOX_WIDTH;
	int endcol = objright / BOX_WIDTH;
	int startrow = objtop / BOX_HEIGHT;
	int endrow = objbot / BOX_HEIGHT;
	//Go through every box in between the starting and ending column and row
	for (int row = startrow; row <= endrow; row++)
	{
		for (int col = startcol; col <= endcol; col++)
		{
			grid[row][col].push_back(obj);	//Add the object pointer to the box
		}
	}
	
	displayGrid();
}

void CollisionManager::delFromGrid(std::shared_ptr<PhysicsObject> obj)
{
	//This function deletes all pointers to an object from all grid boxes it is in

	//Get the four corners of the global bounding rectangle of the object
	float objleft = obj->getBBox().getGlobalBounds().left;
	float objtop = obj->getBBox().getGlobalBounds().top;
	float objright = objleft + obj->getBBox().getGlobalBounds().width;
	float objbot = objtop + obj->getBBox().getGlobalBounds().height;
	printf("Object left,top,right,bot: %f,%f,%f,%f\n", objleft, objtop, objright, objbot);
	//Compute the rows and columns that correspond to the corners of the rectangle
	int startcol = objleft / BOX_WIDTH;
	int endcol = objright / BOX_WIDTH;
	int startrow = objtop / BOX_HEIGHT;
	int endrow = objbot / BOX_HEIGHT;
	//Go through every box in between the starting and ending column and row
	for (int row = startrow; row <= endrow; row++)
	{
		for (int col = startcol; col <= endcol; col++)
		{
			//Search the vector of object pointers at the specific box
			for (auto it = grid[row][col].begin(); it != grid[row][col].end();)
			{
				if (*it == obj)		//If the object pointer is in the vector
				{
					it = grid[row][col].erase(it);	//Erase the object pointer from the vector
				}
				else
					++it;
			}
		}
	}
	
	displayGrid();
}

void CollisionManager::displayGrid()
{
	//Iterates through the entire grid printing out the amount of objects in each box
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			printf("[%d]", grid[i][j].size());
		}
		printf("\n");
	}
}
