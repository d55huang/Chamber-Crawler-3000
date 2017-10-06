#ifndef __BOOSTATK_H_
#define __BOOSTATK_H_

#include "potion.h"
#include <memory>
class Character;

class BoostAtk:public Potion
{
   public:
	BoostAtk();
	void applyItem(std::shared_ptr<Character> h) override;
};

#endif
