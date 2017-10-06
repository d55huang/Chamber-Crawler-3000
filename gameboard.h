#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include <iostream>
#include <vector>
#include <memory>
#include "cell.h"
#include "textdisplay.h"

class Hero;

const int rows = 25;
const int columns = 79;

class GameBoard {
  std::vector<std::vector<std::shared_ptr<Cell>>> Map;
	std::shared_ptr<TextDisplay> td;
	std::shared_ptr<Cell> playercell;
 public:
	GameBoard();
	std::shared_ptr<Cell> getCell(int r, int c);
	void initialize(std::ifstream &file, const std::shared_ptr<Hero> &player);
	void clearMap();
	std::shared_ptr<Cell> getPlayerCell();
  friend std::ostream &operator<<(std::ostream &out, const GameBoard &gb);
};

#endif
