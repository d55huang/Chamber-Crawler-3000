#include "hero.h"
#include <string>
using namespace std;

Hero::Hero(string name, int hp, int atk, int def, int gold_mult) : 
Character{name, hp, atk, def,0,gold_mult} {
	
}

