#include "character.h"
#include <cmath>
#include <algorithm>
using namespace std;

Character::Character(string name, int hp, int atk, int def, int gold, int gold_mult) :
	name{name}, hp{hp}, max_hp{hp}, atk{atk}, def{def}, gold{gold}, gold_mult{gold_mult}{
	char tile = '.';
	cur_loc = tile;
}


int Character::getMult() { return gold_mult; }


string Character::getName() { return name; }


void Character::changeHP(int amount) {
	int newhp = hp + amount;
	if (amount < 0) {
		hp = max(0, newhp);
	} else {
		hp = min(max_hp, newhp);
	}
}


void Character::changeAtk(int amount) {
	int newatk = atk + amount;
	if (amount < 0) {
		atk = max(0, newatk);
	} else {
		atk = newatk;
	}
}


void Character::changeDef(int amount) {
	int newdef = def + amount;
	if (amount < 0) {
		def = max(0, newdef);
	} else {
		def = newdef;
	}
}


char Character::getLoc() { return cur_loc; }
int Character::getGold(){return gold;}
void Character::changeGold(int amount)
{gold += amount;}

void Character::setLoc(char new_loc) { cur_loc = new_loc; }


int Character::getHP() { return hp; }


int Character::getMaxHP() { return max_hp; }


int Character::getAtk() { return atk; }


int Character::getDef() { return def; }


int Character::beStruckBy(shared_ptr<Character> attacker) {
	float hundred = 100;
	int damage = static_cast<int> (ceil((hundred / (hundred + def)) * attacker->getAtk()));
	changeHP(-damage);
	return damage;
}

