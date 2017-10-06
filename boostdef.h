#ifndef __BOOSTDEF_H_
#define __BOOSTDEF_H_

#include "potion.h"
#include <memory>
class Character;

class BoostDef: public Potion
{
   public:
	BoostDef();
	void applyItem(std::shared_ptr<Character>  h)override;
};

#endif
