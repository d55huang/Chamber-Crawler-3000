#ifndef __CELL_H_
#define __CELL_H_

#include <memory>
#include <vector>

class Character;
class Item;
enum class CellType {Character, Item, Stairs, Door, Tile, Wall, Passage, Empty};
class Observer;
class Cell
{
	std::vector < std::shared_ptr<Observer>> observers;
	int x;
	int y;
	char state;
	CellType ct;
	std::shared_ptr<Character> pc;
	std::shared_ptr<Item> pi;
   public:
	Cell(CellType c, char s, std::shared_ptr<Character> ch, std::shared_ptr<Item> i);
	CellType getType();
	std::shared_ptr<Character> & getChar();
	std::shared_ptr<Item> & getItem();
	int getX();
	int getY();
	void setCoords(int xp, int yp);
	void attach(std::shared_ptr<Observer>);
	void detatch(std::shared_ptr<Observer>);
	void notifyObservers();
	void setCell(CellType c, std::shared_ptr<Character> ch, std::shared_ptr<Item> i);
	void setState(char c);
	char getState();
	~Cell();
	
};
#endif
