#include "character.h"
#include "poisonhp.h"
#include <string>

using namespace std;
PoisonHP::PoisonHP():Potion{-10, "Poison Health", "Lose up to 10 HP"}{}

void PoisonHP::applyItem(shared_ptr<Character> h)
{
	int newhp = h->getHP() ;
 
	if (h->getName() == "Elf")
	{
		newhp -=this->getValue();
	}
	else
	{
		newhp += this->getValue();
	}
	if (newhp < 0)
	{
		newhp = 0;
	}

	h->changeHP(newhp - h->getHP());
}
	

