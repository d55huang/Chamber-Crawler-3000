#ifndef _MERCHANT_H_
#define _MERCHANT_H_

#include <memory>
#include "enemy.h"

class Merchant: public Enemy {
	static bool aggroOn;
	public:
	bool getAggro();
	void setAggro();
	int beStruckBy(std::shared_ptr<Character> attacker) override;
	Merchant();
};

#endif
