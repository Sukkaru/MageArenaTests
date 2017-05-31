#pragma once
#include <SFML\Graphics.hpp>
#include "PhysicsObject.h"
#include <unordered_set>
class CollisionManager
{
public:
	CollisionManager(sf::RenderWindow* window);
	~CollisionManager();
	void checkCollisions();
	void addToGrid(std::shared_ptr<PhysicsObject> obj,sf::FloatRect boundingrect);
	void delFromGrid(std::shared_ptr<PhysicsObject> obj, sf::FloatRect boundingrect);
	void updateGrid(std::shared_ptr<PhysicsObject> obj, sf::FloatRect boundingrect, sf::FloatRect prevboundingrect);

private:
	//Grid boxes for spatial partitioning of game world
	//Setting these to 60 for now, can/will adjust later
	//I chose 60 because it is slightly larger than the player
	const int BOX_HEIGHT = 60;
	const int BOX_WIDTH = 60;
	std::vector<std::vector<std::vector<std::shared_ptr<PhysicsObject>>>> grid; //3 dimensions oh my
	std::unordered_set<std::string> collisionpairs;								//Holds pairs of object IDs so objects don't collide more than once if they share multiple grid boxes
	int numboxeswide;
	int numboxeshigh;

	void displayGrid();
	bool checkCollisionGroup(unsigned char collidablegroups, int collisiongroup);
	bool checkBBoxCollision(sf::FloatRect obj1bbox, sf::FloatRect obj2bbox);
};

