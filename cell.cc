#include "cell.h"
#include "character.h"
#include "item.h"
#include <memory>
#include "observer.h"
using namespace std;

int Cell::getX()
{
	return x;
}

int Cell::getY()
{
	return y;
}

void Cell::notifyObservers()
{
	for(auto & o : observers)
	{
		o->notify(*this);
	}
}
void Cell::attach(shared_ptr<Observer> ob)
{
	observers.emplace_back(ob);
}

void Cell::detatch(shared_ptr<Observer> ob)
{
	auto pos = observers.begin()	;
	while (pos != observers.end() && *pos != ob)
	{
		pos ++;
	}
	if (pos != observers.end())
	{
		observers.erase(pos);
	}
}
void Cell::setCoords(int xp, int yp)
{
	x = xp;
	y = yp;
}
Cell::Cell(CellType c,char s, shared_ptr<Character>  ch, shared_ptr<Item> i): state{s} {
	this->setCell(c,ch,i);
	setCoords(-1, -1);
}

CellType Cell::getType() {return ct;}

shared_ptr<Character>& Cell::getChar() { return pc; }

shared_ptr<Item>& Cell::getItem(){return pi;}

char Cell::getState()
{
	return state;
}
void Cell::setState(char c)
{
	state = c;
}

void Cell::setCell(CellType c, shared_ptr<Character> ch, shared_ptr<Item> i)
{
	ct = c;
	pc = nullptr;
	pi = nullptr;

	if (c == CellType::Character)
	{
		pc = ch;
	}
	else if (c == CellType::Item)
	{
		pi = i;
	}
	notifyObservers();	
}

Cell::~Cell()
{
	
}
