// SFMLTemplate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "GameManager.h"




int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 768), "Isaac Is The Man!");	//1280 768
	window.setFramerateLimit(60);
	sf::Clock clock;
	GameManager gameManager(&window);
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		gameManager.Update(&window,&dt);
		gameManager.Draw(&window);
	}

	return 0;
}

