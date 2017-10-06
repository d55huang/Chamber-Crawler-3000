#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "gameboard.h"
#include "hero.h"
#include "item.h"
#include "vampire.h"
#include "werewolf.h"
#include "goblin.h"
#include "troll.h"
#include "dragon.h"
#include "phoenix.h"
#include "merchant.h"
#include "restorehp.h"
#include "boostatk.h"
#include "boostdef.h"
#include "poisonhp.h"
#include "woundatk.h"
#include "wounddef.h"
#include "normal.h"
#include "merchanthoard.h"
#include "smallhorde.h"
#include "dragonhoard.h"

using namespace std;

GameBoard::GameBoard() {
	td = make_shared<TextDisplay>();
}


void GameBoard::clearMap() {
	Map.clear();
}


void GameBoard::initialize(ifstream &file, const shared_ptr<Hero> &player) {

	// Cell Types:

	// Structures: 
	char VERTWALL = '|';
	char HORWALL = '-';
	char DOOR = '+';
	char TILE = '.';
	char PASSAGE = '#';
	char STAIRS = '\\';
	char EMPTY = ' ';

	// Characters:
	char PLAYER = '@';
	char VAMPIRE = 'V';
	char WEREWOLF = 'W';
	char GOBLIN = 'N';
	char MERCHANT = 'M';
	char DRAGON = 'D';
	char PHOENIX = 'X';
	char TROLL = 'T';

	// Items:
	char POTION = 'P';
	char RH = '0';
	char BA = '1';
	char BD = '2';
	char PH = '3';
	char WA = '4';
	char WD = '5';
	char GOLD = 'G';
	char NGOLD = '6';
	char SHORDE = '7';
	char MHORDE = '8';
	char DHORDE = '9';

	for (int c = 0; c < columns; ++c) {
		vector<shared_ptr<Cell>> row{};
		Map.emplace_back(row);
		for (int r = 0; r < rows; ++r) {
			Map[c].emplace_back(nullptr);
		}
	}
	for (int r = 0; r < rows; ++r) {
		string line;
		getline(file, line);
		istringstream ss{line};
		for (int c = 0; c < columns; ++c) {
			char kind;
			ss.get(kind);
			if (kind == VERTWALL) {
				auto p = make_shared<Cell>(CellType::Wall, VERTWALL, nullptr, nullptr);
				Map[c][r] = p;
			} else if (kind == HORWALL) {
				auto p = make_shared<Cell>(CellType::Wall, HORWALL, nullptr, nullptr);
				Map[c][r] = p;
			} else if (kind == DOOR) {
				auto p = make_shared<Cell>(CellType::Door, DOOR, nullptr, nullptr);
				Map[c][r] = p;
			} else if (kind == TILE) {
				auto p = make_shared<Cell>(CellType::Tile, TILE, nullptr, nullptr);
				Map[c][r] = p;
			} else if (kind == PASSAGE) {
				auto p = make_shared<Cell>(CellType::Passage, PASSAGE, nullptr, nullptr);
				Map[c][r] = p;
			} else if (kind == STAIRS) {
				auto p = make_shared<Cell>(CellType::Stairs, STAIRS, nullptr, nullptr);
				Map[c][r] = p;
			} else if (kind == EMPTY) {
				auto p = make_shared<Cell>(CellType::Empty, EMPTY, nullptr, nullptr);
				Map[c][r] = p;
			} else if (kind == PLAYER) {
				auto p = make_shared<Cell>(CellType::Character, PLAYER, player, nullptr);
				Map[c][r] = p;
				Map[c][r]->setCoords(c, r);
				Map[c][r]->attach(td);
				td->notify(*(Map[c][r]));
				playercell = p;
				continue;
			} else if (kind == VAMPIRE) {
				auto vp = make_shared<Vampire>();
				auto p = make_shared<Cell>(CellType::Character, VAMPIRE, vp, nullptr);
				Map[c][r] = p;
			} else if (kind == WEREWOLF) {
				auto wp = make_shared<Werewolf>();
				auto p = make_shared<Cell>(CellType::Character, WEREWOLF, wp, nullptr);
				Map[c][r] = p;
			} else if (kind == GOBLIN) {
				auto gp = make_shared<Goblin>();
				auto p = make_shared<Cell>(CellType::Character, GOBLIN, gp, nullptr);
				Map[c][r] = p;
			} else if (kind == MERCHANT) {
				auto mp = make_shared<Merchant>();
				auto p = make_shared<Cell>(CellType::Character, MERCHANT, mp, nullptr);
				Map[c][r] = p;
			} else if (kind == DRAGON) {
				auto dp = make_shared<Dragon>(nullptr);
				auto p = make_shared<Cell>(CellType::Character, DRAGON, dp, nullptr);
				Map[c][r] = p;
			} else if (kind == PHOENIX) {
				auto pp = make_shared<Phoenix>();
				auto p = make_shared<Cell>(CellType::Character, PHOENIX, pp, nullptr);
				Map[c][r] = p;
			} else if (kind == TROLL) {
				auto tp = make_shared<Troll>();
				auto p = make_shared<Cell>(CellType::Character, TROLL, tp, nullptr);
				Map[c][r] = p;
			} else if (kind == RH) {
				auto rh = make_shared<RestoreHP>();
				auto p = make_shared<Cell>(CellType::Item, POTION, nullptr, rh);
				Map[c][r] = p;
			} else if (kind == BA) {
				auto ba = make_shared<BoostAtk>();
				auto p = make_shared<Cell>(CellType::Item, POTION, nullptr, ba);
				Map[c][r] = p;
			} else if (kind == BD) {
				auto bd = make_shared<BoostDef>();
				auto p = make_shared<Cell>(CellType::Item, POTION, nullptr, bd);
				Map[c][r] = p;
			} else if (kind == PH) {
				auto ph = make_shared<PoisonHP>();
				auto p = make_shared<Cell>(CellType::Item, POTION, nullptr, ph);
				Map[c][r] = p;
			} else if (kind == WA) {
				auto wa = make_shared<WoundAtk>();
				auto p = make_shared<Cell>(CellType::Item, POTION, nullptr, wa);
				Map[c][r] = p;
			} else if (kind == WD) {
				auto wd = make_shared<WoundDef>();
				auto p = make_shared<Cell>(CellType::Item, POTION, nullptr, wd);
				Map[c][r] = p;
			} else if (kind == NGOLD) {
				auto ngp = make_shared<Normal>();
				auto p = make_shared<Cell>(CellType::Item, GOLD, nullptr, ngp);
				Map[c][r] = p;
			} else if (kind == SHORDE) {
				auto shp = make_shared<SmallHorde>();
				auto p = make_shared<Cell>(CellType::Item, GOLD, nullptr, shp);
				Map[c][r] = p;
			} else if (kind == MHORDE) {
				auto mhp = make_shared<MerchantHoard>();
				auto p = make_shared<Cell>(CellType::Item, GOLD, nullptr, mhp);
				Map[c][r] = p;
			} else if (kind == DHORDE) {
				auto dhp = make_shared<DragonHoard>();
				auto p = make_shared<Cell>(CellType::Item, GOLD, nullptr, dhp);
				Map[c][r] = p;
			} else {
				cerr << "Error: Character '" << kind << "' cannot be recognized." << endl;
				return;
			}
			Map[c][r]->setCoords(c, r);
			Map[c][r]->attach(td);
			td->notify(*(Map[c][r]));
		}
	}
}


shared_ptr<Cell> GameBoard::getCell(int x, int y) {
	return Map[x][y];
}


shared_ptr<Cell> GameBoard::getPlayerCell() { return playercell; } 


ostream &operator<<(ostream &out, const GameBoard &gb) {
	out << *(gb.td);
	return out;
}

