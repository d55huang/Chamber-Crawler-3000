#include "enemy.h"
using namespace std;

Enemy::Enemy(string name, int hp, int atk, int def) :
	Character{name, hp, atk, def,0,0} {}

