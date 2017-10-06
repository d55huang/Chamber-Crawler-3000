#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "character.h"

class Enemy: public Character {
	public:
	Enemy(std::string name, int hp, int atk, int def);
};

#endif
