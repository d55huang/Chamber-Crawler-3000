#include "dragonhoard.h"
#include "character.h"

using namespace std;

void DragonHoard::applyItem(shared_ptr<Character> h)
{
	h->changeGold(h->getMult() * this->getValue());
}

DragonHoard::DragonHoard():Treasure{6,"Dragon Hoard"}{}


void DragonHoard::canStep() { steppable = true; }

bool DragonHoard::getStep() { return steppable; }

