#ifndef __MERCHANTHOARD_H_
#define __MERCHANTHOARD_H_

#include "treasure.h"
#include <string>
#include <memory>
class Character;

class MerchantHoard:public Treasure
{	public:
	MerchantHoard();
	void applyItem(std::shared_ptr<Character>  h);
};
#endif
