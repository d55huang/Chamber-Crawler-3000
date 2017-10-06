#include "character.h"
#include "woundatk.h"
#include <string>

using namespace std;
WoundAtk::WoundAtk():Potion{-5, "Wound Attack", "Lose up to 5 ATK"}{}

void WoundAtk::applyItem(shared_ptr<Character> h)
{
	int newatk = h->getAtk();
 
	if (h->getName() == "Elf")
	{
		newatk -= this->getValue();
	}
	else
	{
		newatk += this->getValue();
	}
	if (newatk < 0)
	{
		newatk = 0;
	}

	h->changeAtk(newatk - h->getAtk());
}
	

