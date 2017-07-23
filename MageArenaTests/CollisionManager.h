#pragma once
#include <SFML\Graphics.hpp>
#include "PhysicsObject.h"
#include <unordered_set>
class CollisionManager
{
public:
	CollisionManager(int arenaWidth, int arenaHeight);
	~CollisionManager();
	void checkCollisions();
	void addToGrid(std::shared_ptr<PhysicsObject> obj,sf::FloatRect boundingRect);
	void delFromGrid(std::shared_ptr<PhysicsObject> obj, sf::FloatRect boundingRect);
	void updateGrid(std::shared_ptr<PhysicsObject> obj, sf::FloatRect boundingRect, sf::FloatRect previousBoundingRect);

private:
	//Grid boxes for spatial partitioning of game world
	//Setting these to 60 for now, can/will adjust later
	//I chose 60 because it is slightly larger than the player
	const int BOX_HEIGHT = 60;
	const int BOX_WIDTH = 60;
	std::vector<std::vector<std::vector<std::shared_ptr<PhysicsObject>>>> m_grid; //3 dimensions oh my
	std::unordered_set<std::string> m_collisionPairs;								//Holds pairs of object IDs so objects don't collide more than once if they share multiple grid boxes
	int m_nBoxesWide;
	int m_nBoxesHigh;

	void displayGrid();
	bool checkCollisionGroup(unsigned char collidableGroups, int collisionGroup);
	sf::FloatRect createCollisionRect(sf::FloatRect obj1BoundingBox, sf::FloatRect obj2BoundingBox);
	bool checkRectForCollision(sf::FloatRect collisionRect);
};

