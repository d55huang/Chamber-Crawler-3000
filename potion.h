#ifndef __POTION_H_
#define __POTION_H_

#include "item.h"
#include <string>
#include <memory>
class Character;

class Potion:public Item
{
	std::string effect;
   public:
	Potion(int val, std::string name, std::string eff);
	std::string getEffect();
	virtual void applyItem(std::shared_ptr<Character>  h) = 0;
};



#endif
