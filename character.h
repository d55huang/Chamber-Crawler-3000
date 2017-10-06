#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <string>
#include <memory>

class Character {
	std::string name;
	int hp;
	int max_hp;
	int atk;
	int def;
	int gold;
	int gold_mult;
	char cur_loc = '.';
	public:
	Character(std::string name, int hp, int atk, int def, int gold, int gold_mult);
	std::string getName();
	int getHP();
	int getMaxHP();
	int getAtk();
	int getDef();
	char getLoc();
	int getGold();
	int getMult();
	void setLoc(char new_loc);
  void changeGold(int amount);
	void changeHP(int amount);
	void changeAtk(int amount);
	void changeDef(int amount);
	virtual int beStruckBy(std::shared_ptr<Character> attacker);
};

#endif
