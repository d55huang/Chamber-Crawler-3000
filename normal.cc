#include "normal.h"
#include "character.h"
using namespace std;
void Normal::applyItem(shared_ptr<Character> h)
{
	h->changeGold(h->getMult() * this->getValue());
}
Normal::Normal():Treasure{1,"Normal"}{}
