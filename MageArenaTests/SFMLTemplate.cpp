// SFMLTemplate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "GameManager.h"




int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	sf::Clock clock;
	GameManager gameManager;
	while (window.isOpen())
	{
		gameManager.Update(&window,&clock);
		gameManager.Draw(&window);

	}

	return 0;
}

