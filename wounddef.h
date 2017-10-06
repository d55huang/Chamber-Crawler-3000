#ifndef __WOUNDDEF_H_
#define __WOUNDDEF_H_

#include "potion.h"
#include <memory>
class Character;

class WoundDef: public Potion
{
   public:
	WoundDef();
	void applyItem(std::shared_ptr<Character> h) override;
};

#endif
