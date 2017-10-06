#ifndef __RESTOREHP_H_
#define __RESTOREHP_H_

#include "potion.h"
#include <memory>
class Character;

class RestoreHP:public Potion
{
   public:
	RestoreHP();
	void applyItem(std::shared_ptr<Character> h) override;
};

#endif
