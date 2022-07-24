#include <iostream>
#include <set>

#include <SFML/Graphics.hpp>
class Cell
{
public:
//	bool Occupied;
	const static int CellSize = 120;
	enum Options
	{
		UP = 1,
		DOWN = 2,
		LEFT = 3,
		RIGHT = 4,
		CENTER = 5,
		NONE = 6,
	};
	int Entropy = 5;
	Options Dir;
	std::set<Cell::Options> States;
	Cell()
	{
		Dir = NONE;
	}
};

class Canvas
{
public:
	sf::Texture textRight;
	sf::Texture textDown;
	sf::Texture textLeft;
	sf::Texture textUp;
	sf::Texture textCenter;
	sf::Texture textNone;
	
	sf::Sprite sprite;
	const float Scale = 0.33;
	const static int SizeX = 20;
	const static int SizeY = 20;
		
	Cell cells[SizeX][SizeY];	
	Canvas();
//	template <size_t rows, size_t cols>
//		void CalculateEntropy(Cell (&cl)[rows][cols]);
	void DrawCells(sf::RenderWindow* window, int Size);
};
