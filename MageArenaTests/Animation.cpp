#include "stdafx.h"
#include "Animation.h"


Animation::Animation(sf::Texture* texture, sf::Vector2u texturerectsize, float switchtime)
{
	this->switchtime = switchtime;
	totaltime = 0;
	currentimage.x = 0;

	texturerect.width = texturerectsize.x;
	texturerect.height = texturerectsize.y;
}


Animation::~Animation()
{
}

void Animation::Update(float dt, int row, int endcol, int startcol)
{
	currentimage.y = row;
	totaltime += dt;

	if (totaltime >= switchtime)
	{
		totaltime -= switchtime;
		currentimage.x++;

		if (currentimage.x >= endcol)
		{
			currentimage.x = startcol;
		}
	}

	texturerect.left = currentimage.x * texturerect.width;
	texturerect.top = currentimage.y * texturerect.height;
}

sf::IntRect Animation::getTextureRect()
{
	return texturerect;
}
