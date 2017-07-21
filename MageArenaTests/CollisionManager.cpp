#include "stdafx.h"
#include "CollisionManager.h"


CollisionManager::CollisionManager(int arenawidth, int arenaheight)
{
	//Determine how many boxes needed
	//Add one to account for possible rounding down
	numboxeswide = (arenawidth / BOX_WIDTH) + 1;
	numboxeshigh = (arenaheight / BOX_HEIGHT) + 1;
	printf("High:%d \n Wide:%d \n", numboxeshigh, numboxeswide);
	//Make sure the grid has allocated enough space for all boxes
	grid = std::vector<std::vector<std::vector<std::shared_ptr<PhysicsObject>>>>(numboxeshigh, std::vector<std::vector<std::shared_ptr<PhysicsObject>>>(numboxeswide, std::vector<std::shared_ptr<PhysicsObject>>()));
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::checkCollisions()
{
	//Empty the set of collision pairs
	collisionpairs.clear();
	//Just iterating through the entire grid for now
	//If this is too slow it can be optimized
	//displayGrid();
	for (int row = 0; row < grid.size(); row++)
	{
		for (int col = 0; col < grid[row].size(); col++)
		{
			for (int obj = 0; obj < grid[row][col].size(); obj++)
			{
				for (int obj2 = obj + 1; obj2 < grid[row][col].size(); obj2++)
				{
					//Compare stuff here
					//If obj can collide with obj2's group
					if (checkCollisionGroup(grid[row][col][obj]->getCollidableGroups(), grid[row][col][obj2]->getCollisionGroup()) == true)
					{
						//If this object pair has not been checked for collisions yet
						if (collisionpairs.count(grid[row][col][obj]->getCollisionID() + ":" + grid[row][col][obj2]->getCollisionID()) == 0)
						{
							sf::FloatRect collisionrect = createCollisionRect(grid[row][col][obj]->getBBox(), grid[row][col][obj2]->getBBox());
							//Check if there is an actual collision
							if (checkRectForCollision(collisionrect) == true)
							{
								//printf("Collision!\n");
								grid[row][col][obj]->resolveCollision(grid[row][col][obj2], collisionrect);
								grid[row][col][obj2]->resolveCollision(grid[row][col][obj], collisionrect);
								//Add the pair of objects to the collision pair set
								//This prevents the objects from being checked for collision more than once
								collisionpairs.insert(grid[row][col][obj]->getCollisionID() + ":" + grid[row][col][obj2]->getCollisionID());
							}
						}
					}
				}
			}
		}
	}
}

void CollisionManager::addToGrid(std::shared_ptr<PhysicsObject> obj, sf::FloatRect boundingrect)
{
	//This function takes an object, gets the position of the object
	//and adds the object to the vector of the grid squares that it is in
	
	//Get the four corners of the global bounding rectangle of the object
	float objleft = boundingrect.left;
	float objtop = boundingrect.top;
	float objright = objleft + boundingrect.width;
	float objbot = objtop + boundingrect.height;
	//printf("Object left,top,right,bot: %f,%f,%f,%f\n", objleft, objtop, objright, objbot);
	//Compute the rows and columns that correspond to the corners of the rectangle
	int startcol = objleft / BOX_WIDTH;
	int endcol = objright / BOX_WIDTH;
	int startrow = objtop / BOX_HEIGHT;
	int endrow = objbot / BOX_HEIGHT;
	//Go through every box in between the starting and ending column and row
	for (int row = startrow; row <= endrow; row++)
	{
		if (row > -1 && row < numboxeshigh)
		{
			for (int col = startcol; col <= endcol; col++)
			{
				if (col > -1 && col < numboxeswide)
				{
					grid[row][col].push_back(obj);	//Add the object pointer to the box
				}
			}
		}
	}
	
	//displayGrid();
}

void CollisionManager::delFromGrid(std::shared_ptr<PhysicsObject> obj, sf::FloatRect boundingrect)
{
	//This function deletes all pointers to an object from all grid boxes it is in

	//Get the four corners of the global bounding rectangle of the object
	float objleft = boundingrect.left;
	float objtop = boundingrect.top;
	float objright = objleft + boundingrect.width;
	float objbot = objtop + boundingrect.height;
	//printf("Object left,top,right,bot: %f,%f,%f,%f\n", objleft, objtop, objright, objbot);
	//Compute the rows and columns that correspond to the corners of the rectangle
	int startcol = objleft / BOX_WIDTH;
	int endcol = objright / BOX_WIDTH;
	int startrow = objtop / BOX_HEIGHT;
	int endrow = objbot / BOX_HEIGHT;
	//Go through every box in between the starting and ending column and row
	for (int row = startrow; row <= endrow; row++)
	{
		if (row > -1 && row < numboxeshigh)
		{
			for (int col = startcol; col <= endcol; col++)
			{
				if (col > -1 && col < numboxeswide)
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
		}
	}
	
	//displayGrid();
}

void CollisionManager::updateGrid(std::shared_ptr<PhysicsObject> obj, sf::FloatRect boundingrect, sf::FloatRect prevboundingrect)
{
	//First delete the object from the grid
	delFromGrid(obj,prevboundingrect);
	//Then add it back in to the grid
	addToGrid(obj,boundingrect);
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
	printf("\n");
}

bool CollisionManager::checkCollisionGroup(unsigned char collidablegroups, int collisiongroup)
{
	unsigned char mask = 1;							//Initialize the bitmask
	mask = mask << collisiongroup;					//Shift the active bit over to the slot that corresponds to the collision group
	return (collidablegroups & mask) > 0;			//If there is a 1 in the slot that corresponds to that group, the objects can collide
}

sf::FloatRect CollisionManager::createCollisionRect(sf::FloatRect obj1bbox, sf::FloatRect obj2bbox)
{
	float obj1left = obj1bbox.left;
	float obj1top = obj1bbox.top;
	float obj1right = obj1bbox.left + obj1bbox.width;
	float obj1bot = obj1bbox.top + obj1bbox.height;

	float obj2left = obj2bbox.left;
	float obj2top = obj2bbox.top;
	float obj2right = obj2bbox.left + obj2bbox.width;
	float obj2bot = obj2bbox.top + obj2bbox.height;
	//Create the collision rectangle
	float rectleft = std::max(obj1left, obj2left);
	float recttop = std::max(obj1top, obj2top);
	float rectright = std::min(obj1right, obj2right);
	float rectbot = std::min(obj1bot, obj2bot);

	sf::FloatRect collisionrect = sf::FloatRect(rectleft, recttop, rectright - rectleft, rectbot - recttop);
	return collisionrect;
}

bool CollisionManager::checkRectForCollision(sf::FloatRect collisionrect)
{
	return collisionrect.left < (collisionrect.left + collisionrect.width) && collisionrect.top < (collisionrect.top + collisionrect.height);
}
