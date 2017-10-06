#ifndef __POISONHP_H_
#define __POISONHP_H_

#include "potion.h"
#include <memory>
class Character;

class PoisonHP: public Potion
{
   public:
	PoisonHP();
	void applyItem(std::shared_ptr<Character> h) override;
};

#endif
