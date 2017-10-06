#ifndef _GAME_H_
#define _GAME_H_

#include <fstream>
#include <memory>
#include <vector>
#include "gameboard.h"
#include "enemy.h"

class Game {
	GameBoard gb;
	int maxfloor = 5;
	std::shared_ptr<Cell> playercell;
	std::vector<std::vector<std::shared_ptr<Cell>>> chambers;
	std::vector<std::shared_ptr<Cell>> enemies;
	bool checkloc(std::shared_ptr<Cell> loc, char kind);
	bool missAtk();
	void move(std::shared_ptr<Cell> ori, std::shared_ptr<Cell> dest);
	void use(std::shared_ptr<Hero> user, std::shared_ptr<Cell> itemcell);
	int attack(std::shared_ptr<Cell> attackercell, std::shared_ptr<Cell> defendercell);
	std::shared_ptr<Cell> generateLocation();
	void printStats(std::shared_ptr<Hero> pc, const std::string &action, int floor);
	int member(std::shared_ptr<Cell> target);
	void makeChambers();
	void addChamber(int row, int col, std::vector<std::shared_ptr<Cell>> &cham);
	void generateElements();
	std::shared_ptr<Cell> checksurr(std::shared_ptr<Cell> loc, char kind);
	void initializeEnemies();
	void sortEnemies();
	std::shared_ptr<Cell> gensurr(std::shared_ptr<Cell> targ);
	public:
	bool defaultmap = true;
	void playGame(std::string filename);
};

#endif
