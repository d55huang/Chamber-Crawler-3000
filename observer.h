#ifndef __OBSERVER_H_
#define __OBSERVER_H_

class Cell;
class Observer
{
   public: 
	virtual void notify(Cell & s) = 0; 
	virtual ~Observer();
};

#endif
