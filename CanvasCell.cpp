
#include <iostream>
#include <set>
#include "CanvasCell.h"

#include <SFML/Graphics.hpp>
Canvas::Canvas()
{
	if (!textRight.loadFromFile("Textures/Right.jpg"))
	{
    	std::cerr<< "not loaded right\n";// error...
	}
	if (!textDown.loadFromFile("Textures/Down.jpg"))
	{
    	std::cerr<< "not loaded down\n";// error...
	}
	if (!textLeft.loadFromFile("Textures/Left.jpg"))
	{
    	std::cerr<< "not loaded left\n";// error...
	}
	if (!textUp.loadFromFile("Textures/Up.jpg"))
	{
    	std::cerr<< "not loaded up\n";// error...
	}
	if (!textCenter.loadFromFile("Textures/Center.jpg"))
	{
    	std::cerr<< "not loaded center\n";// error...
	}
		if (!textNone.loadFromFile("Textures/None.jpg"))
	{
    	std::cerr<< "not loaded none\n";// error...
	}

	sprite.setTexture(textDown);
	sprite.setScale(Scale, Scale);
}

void Canvas::DrawCells(sf::RenderWindow* window, int Size)
{
	int i, j;
	for (i = 0; i < Size; i++)
	{
		for (j = 0; j < Size; j++)
		{
			switch (cells[i][j].Dir)
			{
				case Cell::NONE:
					sprite.setTexture(textNone);
				break;
				case Cell::RIGHT:
					sprite.setTexture(textRight);
				break;
				case Cell::LEFT:
					sprite.setTexture(textLeft);
				break;
				case Cell::UP:
					sprite.setTexture(textUp);
				break;
				case Cell::DOWN:
					sprite.setTexture(textDown);
				break;
				case Cell::CENTER:
					sprite.setTexture(textCenter);
				break;	
			};	
			sprite.setPosition(i*Cell::CellSize*Scale, j*Cell::CellSize*Scale);
			window->draw(sprite);	
		}
	}
}
