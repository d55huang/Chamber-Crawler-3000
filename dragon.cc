#include "dragon.h"
#include "dragonhoard.h"
using namespace std;

Dragon::Dragon(shared_ptr<Cell> hoard) : Enemy{"Dragon", 150, 20, 20}, hoard{hoard} {}


Dragon::~Dragon() {
	auto hoardpt = dynamic_pointer_cast<DragonHoard>(hoard->getItem());
	hoardpt->canStep();
}


void Dragon::setHoard(shared_ptr<Cell> dhoard) {
	hoard = dhoard;
}


shared_ptr<Cell> Dragon::getHoard() { return hoard; }

