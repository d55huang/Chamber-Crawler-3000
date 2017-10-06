#ifndef __DRAGONHOARD_H_
#define __DRAGONHOARD_H_

#include "treasure.h"
#include <string>
#include <memory>
class Character;
class DragonHoard:public Treasure
{
	bool steppable = false;
	public:
	DragonHoard();
	void applyItem(std::shared_ptr<Character>  h);
	void canStep();
	bool getStep();
};
#endif

