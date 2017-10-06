#include <iostream>
#include "gameboard.h"
#include "cell.h"

using namespace std;


TextDisplay::TextDisplay()
{
	for (int c = 0;  c < columns; c ++)
	{
		vector<char> v;
		
		for (int r = 0; r < rows; r ++)
		{
			v.emplace_back(EMPTY);
		}
		
		td.emplace_back(v);
	}
};
	
void TextDisplay::notify(Cell & c)
{
	td[c.getX()][c.getY()] = c.getState();
}

TextDisplay::~TextDisplay()
{
	for (int i = 0; i < columns; i++)
	{
		td[i].clear();
	}
	td.clear();
}
			

std::ostream & operator << (std::ostream & out, const TextDisplay & t)
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)

		{
			out << t.td[c][r];
		}
		out << endl;
	}
	return out;
}


