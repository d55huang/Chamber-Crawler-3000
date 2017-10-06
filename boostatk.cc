#include "character.h"
#include "boostatk.h"
#include <string>
using namespace std;
BoostAtk::BoostAtk():Potion{5, "Boost Attack", "Increases ATK by 5"}{}

void BoostAtk::applyItem(shared_ptr<Character> h)
{

	h->changeAtk(this->getValue());
}
	

