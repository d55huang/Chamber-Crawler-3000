#ifndef __TREASURE_H_
#define __TREASURE_H_

#include <string>
#include "item.h"
#include <memory>
class Character;

class Treasure: public Item
{	
   public:
	Treasure(int mod, std::string st);
	virtual	void applyItem(std::shared_ptr<Character> h ) = 0;
};

#endif
