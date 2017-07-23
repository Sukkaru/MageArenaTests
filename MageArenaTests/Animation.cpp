#include "stdafx.h"
#include "Animation.h"


Animation::Animation(sf::Texture* texture, sf::Vector2u textureRectSize, float switchTime)
{
	m_switchTime = switchTime;
	m_totalTime = 0;
	m_currentImage.x = 0;

	m_textureRect.width = textureRectSize.x;
	m_textureRect.height = textureRectSize.y;
}


Animation::~Animation()
{
}

void Animation::update(float dt, int row, int endColumn, int startColumn)
{
	m_currentImage.y = row;
	m_totalTime += dt;

	if (m_totalTime >= m_switchTime)
	{
		m_totalTime -= m_switchTime;
		m_currentImage.x++;

		if (m_currentImage.x >= endColumn)
		{
			m_currentImage.x = startColumn;
		}
	}

	m_textureRect.left = m_currentImage.x * m_textureRect.width;
	m_textureRect.top = m_currentImage.y * m_textureRect.height;
}

sf::IntRect Animation::getTextureRect()
{
	return m_textureRect;
}
