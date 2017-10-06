#ifndef __ITEM_H_
#define __ITEM_H_
#include <memory>
#include <string>

class Character;

class Item
{
	char steppingOn;
	int modifier;
	std::string name;
   public:
	Item(int mod, std::string st);
	virtual	void applyItem(std::shared_ptr<Character>  h) =0;
	int getValue();
	char getStep();
	std::string getName();
};
	



#endif
