#ifndef __SMALLHORDE_H_
#define __SMALLHORDE_H_

#include "treasure.h"
#include <string>
#include <memory>
class Character;
class SmallHorde:public Treasure
{


	public:
	void applyItem(std::shared_ptr<Character>  h) override;
	SmallHorde();
};
#endif
