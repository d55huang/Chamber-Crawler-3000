#ifndef __TEXTDISPLAY_H_
#define __TEXTDISPLAY_H_

#include <iostream>
#include <vector>
#include "observer.h"

class Cell;
class TextDisplay: public Observer
{
	const char EMPTY = ' ';
	std::vector< std::vector < char > > td; //rows of columns
   public:
	TextDisplay();                // initialize each cell as EMPTY
	void notify(Cell & s)override;
	~TextDisplay();

friend std::ostream & operator << (std::ostream & out, const TextDisplay & td);
};
#endif
