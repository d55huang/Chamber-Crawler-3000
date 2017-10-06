#include "potion.h"
#include <string>
#include "hero.h"
using namespace std;

Potion::Potion(int val, string name, string eff):Item{val,name}, effect{eff} {}
string Potion::getEffect()
{
	return effect;
}

