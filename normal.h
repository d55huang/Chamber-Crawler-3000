#ifndef __NORMAL_H_
#define __NORMAL_H_

#include "treasure.h"
#include <string>
#include<memory>
class Character;
class Normal:public Treasure
{

	public:
	Normal();
	void applyItem(std::shared_ptr<Character> h) override;
};
#endif
