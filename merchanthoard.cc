#include "merchanthoard.h"
#include "character.h"
using namespace std;

void MerchantHoard::applyItem(shared_ptr<Character>  h)
{
	h->changeGold(h->getMult() * this->getValue());
}
MerchantHoard::MerchantHoard():Treasure{4,"Merchant Hoard"}{}
