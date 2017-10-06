#include "character.h"
#include "wounddef.h"
#include <string>

using namespace std;
WoundDef::WoundDef():Potion{-5, "Wound Defence", "Lose up to 5 DEF"}{}

void WoundDef::applyItem(shared_ptr<Character> h)
{
	int newdef = h->getDef();
 if (h->getName() == "Elf")
 {
		newdef -=	 this->getValue();
 }
 else
 {
	 newdef += this->getValue();
 }
	if (newdef < 0)
	{
		newdef = 0;
	}

	h->changeDef(newdef - h->getDef());
}
	

