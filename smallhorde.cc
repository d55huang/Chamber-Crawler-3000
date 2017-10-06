#include "smallhorde.h"
#include "character.h"
using namespace std;
void SmallHorde::applyItem(shared_ptr<Character> h)
{
	h->changeGold(h->getMult() * this->getValue());
}
SmallHorde::SmallHorde():Treasure{2,"Small Horde"} {}
