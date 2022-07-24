#include <iostream>
#include <set>

#include "CanvasCell.h"
#include <SFML/Graphics.hpp>
//-std=c++11
//-std=gnu++11
/*-lsfml-audio
-lsfml-graphics
-lsfml-window
-lsfml-system*/ 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


enum SideOfNeighbour
{
	SideLeft,
	SideRight,
	SideUp,
	SideDown,
};


void ExcludeStates(std::set<Cell::Options> & vect, Cell::Options Dir, SideOfNeighbour Side)
{
	if(Side == SideLeft)
	{
		if(Dir == Cell::DOWN || Dir == Cell::UP || Dir == Cell::RIGHT)
		{
			vect.erase(Cell::RIGHT);
			vect.erase(Cell::CENTER);

		}
		if(Dir == Cell::CENTER || Dir == Cell::LEFT)
		{
			vect.erase(Cell::UP);
			vect.erase(Cell::DOWN);
			vect.erase(Cell::LEFT);
		}
	}
	
	if(Side == SideRight)
	{
		if(Dir == Cell::DOWN || Dir == Cell::UP || Dir == Cell::LEFT)
		{		
			vect.erase(Cell::LEFT);
			vect.erase(Cell::CENTER);	
		}
		if(Dir == Cell::CENTER || Dir == Cell::RIGHT)
		{
			vect.erase(Cell::UP);
			vect.erase(Cell::DOWN);
			vect.erase(Cell::RIGHT);
		}
	}
	
	if(Side == SideUp)
	{
		if(Dir == Cell::DOWN || Dir == Cell::RIGHT || Dir == Cell::LEFT)
		{
			vect.erase(Cell::DOWN);
			vect.erase(Cell::CENTER);
		}
		if(Dir == Cell::CENTER || Dir == Cell::UP)
		{
			vect.erase(Cell::UP);
			vect.erase(Cell::LEFT);
			vect.erase(Cell::RIGHT);
		}
	}
	
	if(Side == SideDown)
	{
		if(Dir == Cell::UP || Dir == Cell::RIGHT || Dir == Cell::LEFT)
		{
			vect.erase(Cell::UP);
			vect.erase(Cell::CENTER);			
		}
		if(Dir == Cell::CENTER || Dir == Cell::DOWN)
		{
			vect.erase(Cell::DOWN);
			vect.erase(Cell::LEFT);
			vect.erase(Cell::RIGHT);
		}
	}
}

template <size_t rows, size_t cols>
	void CalculateEntropy(Cell (&cl)[rows][cols])
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (cl[i][j].Dir != Cell::NONE)
			{
				cl[i][j].Entropy = 0;	
			}
			else
			{
				bool NoNeighh = true;
				cl[i][j].States.insert(Cell::UP);
				cl[i][j].States.insert(Cell::DOWN);
				cl[i][j].States.insert(Cell::CENTER);
				cl[i][j].States.insert(Cell::LEFT);
				cl[i][j].States.insert(Cell::RIGHT);	
			
				if (i != 0)
				{
					if (cl[i-1][j].Dir != Cell::NONE) 
					{
		
						ExcludeStates(cl[i][j].States, cl[i-1][j].Dir, SideLeft);
						NoNeighh = false;
					}
					else cl[i][j].States.insert(Cell::NONE);// vse sostojaniia;
				}
				if (i != rows-1)
				{
					if (cl[i+1][j].Dir != Cell::NONE) 
					{
	
						ExcludeStates(cl[i][j].States, cl[i+1][j].Dir, SideRight);
						NoNeighh = false;
					}
					else cl[i][j].States.insert(Cell::NONE);// vse sostojaniia;
				}
				if (j != 0)
				{
					if (cl[i][j-1].Dir != Cell::NONE)
					{
	
						ExcludeStates(cl[i][j].States, cl[i][j-1].Dir, SideUp);
						NoNeighh = false;
					}
					else cl[i][j].States.insert(Cell::NONE);
				}
				if (j != rows+1)
				{
					if (cl[i][j+1].Dir != Cell::NONE)
					{	
	
					    ExcludeStates(cl[i][j].States, cl[i][j+1].Dir, SideDown);
						NoNeighh = false;
					}
					else cl[i][j].States.insert(Cell::NONE);
				}
				
				if (NoNeighh == true)
				{
					cl[i][j].Dir = Cell::NONE;
					cl[i][j].Entropy = 5;
				}
				else
				{
					cl[i][j].Entropy = 0;
					for(auto it : cl[i][j].States)
					{
						if(it != Cell::NONE)
							cl[i][j].Entropy++;
					}
					// to do Calculate Entropy from the PossibleStates
					// if Possible states = 1 then set state;
				}
		//		std::cout << i << "  " <<  j << "  " << cl[i][j].Entropy << " \n";
			}
		}
	}
}

// nado opredelit' entropiju
// posle etogo zadat' sostojanija
template <size_t rows, size_t cols>
	void LowestEntropyCell(Cell (&arr)[rows][cols], Cell *& cell)
{
	int i, j;
	int temp = 5;//arr[0][0].Entropy;
	bool found = false;
	int temp_i = 0, temp_j = 0;
	cell = &arr[0][0];
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (arr[i][j].Entropy < temp && arr[i][j].Entropy!=0)
			{
				temp = arr[i][j].Entropy;
				cell = &arr[i][j];
				temp_i = i;
				temp_j = j;
				found = true;
			}
		}
	}
//	if (found)
//	std::cout << temp_i << "  " <<  temp_j << "  " << cell->Entropy << " \n";
}
void SetPosition(Cell *&LECell)
{
	LECell->States.erase(Cell::NONE);
	int States = LECell->States.size();
	int State = rand()%States;

//	std::cout <<" Size "<<States <<"\n";
	if (States!=5)
	{
		if(LECell->States.size() == 0) 	std::cout <<" no suitable title \n";
		auto it = LECell->States.begin();
		std::advance(it, State);
//		std::cout <<LECell->Entropy<< "   " << State << " \n";
//	it+=State;
		LECell->Dir = *it;
	}
	
}
void BuildMap(Canvas *Background)
{
	int Loops = 1000;
	int i;
	for (i = 0; i< Loops; i++)
	{
		Cell *LECell = nullptr;
		CalculateEntropy<Canvas::SizeX, Canvas::SizeY>(Background->cells);
		LowestEntropyCell<Canvas::SizeX, Canvas::SizeY>(Background->cells, LECell);
		if (LECell!= nullptr )
		{
			SetPosition(LECell);	
		}
		else
			std::cout<< "not found!\n";
		
		
	}	
}
int main(int argc, char** argv) 
{
	sf::RenderWindow window(sf::VideoMode(640,480),
    "Rendering the rectangle.");

  // Creating our shape.
 // 	sf::RectangleShape rectangle(sf::Vector2f(128.0f,128.0f));
 // 	rectangle.setFillColor(sf::Color::Red);
  //	rectangle.setPosition(320,240);
 // 	rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
  	
  //	sf::Texture textRight;
	
	Canvas Background;
	Background.cells[1][5].Dir = Cell::DOWN;
	Background.cells[2][2].Dir = Cell::UP;
	
 
	
	BuildMap(&Background);

  	while(window.isOpen())
	{
    	sf::Event event;
   		while(window.pollEvent(event))
		{
      		if(event.type == sf::Event::Closed)
			{
        // Close window button clicked.
        		window.close();
      		}
    	}
    	window.clear(sf::Color::Black);
    //	window.draw(rectangle); // Drawing our shape.
    	Background.DrawCells(&window, 20);
   // 	window.draw(sprite);
    	window.display();
  	}
}

