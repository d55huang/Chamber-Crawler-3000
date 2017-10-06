#include "character.h"
#include "boostdef.h"
#include <string>
using namespace std;
BoostDef::BoostDef():Potion{5, "Boost Defence", "Increases DEF by 5"}{}

void BoostDef::applyItem(shared_ptr<Character> h)
{
	h->changeDef(this->getValue());
}
	

