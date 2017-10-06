#include "item.h"
using namespace std;

Item::Item(int mod, string st):steppingOn{'.'},modifier{mod}, name{st} {}

int Item::getValue(){
	return modifier;
}

char Item::getStep()
{
	return steppingOn;
}

string Item::getName() { return name; }

