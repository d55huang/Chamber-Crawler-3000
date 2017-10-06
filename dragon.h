#ifndef _DRAGON_H_
#define _DRAGON_H_
#include "enemy.h"
#include "cell.h"
#include <memory>

class DragonHoard;

class Dragon: public Enemy {
	std::shared_ptr<Cell> hoard;
	public:
	Dragon(std::shared_ptr<Cell> hoard);
	std::shared_ptr<Cell> getHoard();
	void setHoard(std::shared_ptr<Cell> dhoard);
	~Dragon();
};

#endif
