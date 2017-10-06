#ifndef _HERO_H_
#define _HERO_H_
#include "character.h"

class Hero: public Character {
	public:
	Hero(std::string name, int hp, int atk, int def, int gold_mult);
};

#endif
