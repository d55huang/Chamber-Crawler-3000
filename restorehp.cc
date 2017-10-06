#include "character.h"
#include "restorehp.h"
#include <string>
using namespace std;
RestoreHP::RestoreHP():Potion{10, "Restore Health", "Restores up to 10 HP"}{}

void RestoreHP::applyItem(shared_ptr<Character> h)
{
	int newhp = h->getHP()+this->getValue();
	
	if (newhp > h->getMaxHP())
	{
		newhp = h->getMaxHP();
	}

	h->changeHP(newhp - h->getHP() );
}
	

