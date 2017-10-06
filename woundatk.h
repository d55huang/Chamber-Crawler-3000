#ifndef __WOUNDATK_H_
#define __WOUNDATK_H_

#include "potion.h"
#include <memory>
class Character;

class WoundAtk:public Potion
{
   public:
	WoundAtk();
	void applyItem(std::shared_ptr<Character> h) override;
};

#endif
