#include "merchant.h"
#include <cmath>
using namespace std;

bool Merchant::aggroOn = false;

Merchant::Merchant() : Enemy{"Merchant", 30, 70, 5} {}


bool Merchant::getAggro() { return aggroOn; }


void Merchant::setAggro() { aggroOn = true; }


int Merchant::beStruckBy(shared_ptr<Character> attacker) {
	setAggro();
	float hundred = 100;
	int damage = static_cast<int>(ceil((hundred / (hundred + getDef())) * attacker->getAtk()));
	changeHP(-damage);
	return damage;
}

