#include <cstdlib>
#include <ctime>
#include <iostream>
#include "game.h"
#include "item.h"
#include "hero.h"
#include "human.h"
#include "elf.h"
#include "orc.h"
#include "dwarf.h"
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

static bool find_vec (shared_ptr<Cell> c, vector<shared_ptr<Cell>> v)
{
	for (auto i : v)
	{
		if (c->getX() == i->getX() && c->getY() == i->getY()) return true;
	}
	return false;
}


void Game::sortEnemies()
{
	int NUM_ENEMY = enemies.size();
	for (int p = 0; p < NUM_ENEMY ; p ++)
	{
		for (int i = p; i > 0; i--)
		{
			int x1 = enemies[i-1]->getX();
			int y1 = enemies[i-1]->getY();
			int x2 = enemies[i]->getX();
			int y2 = enemies[i]->getY();

			using std::swap;
			if (y1 >y2 || (y1 == y2 && x1 > x2))
			{
				swap(enemies[i-1], enemies[i]);
			}
		}
	}
}


shared_ptr<Cell> Game::checksurr(shared_ptr<Cell> loc, char kind) {
	int locx = loc->getX();
	int locy = loc->getY();
	auto no = gb.getCell(locx, locy-1);
	if (checkloc(no, kind)) return no;
	auto ea = gb.getCell(locx+1, locy);
	if (checkloc(ea, kind)) return ea;
	auto so = gb.getCell(locx, locy+1);
	if (checkloc(so, kind)) return so;
	auto we = gb.getCell(locx-1, locy);
	if (checkloc(we, kind)) return we;
	auto ne = gb.getCell(locx+1, locy-1);
	if (checkloc(ne, kind)) return ne;
	auto nw = gb.getCell(locx-1, locy-1);
	if (checkloc(nw, kind)) return nw;
	auto se = gb.getCell(locx+1, locy+1);
	if (checkloc(se, kind)) return se;
	auto sw = gb.getCell(locx-1, locy+1);
	if (checkloc(sw, kind)) return sw;
	return nullptr;
}


shared_ptr<Cell> Game::gensurr(shared_ptr<Cell> targ) {
	int cellx = targ->getX();
	int celly = targ->getY();
	shared_ptr<Cell> cell;
	while (true) {
		int randnum = rand() % 8;
		if (randnum == 0) {
			cell = gb.getCell(cellx-1, celly+1);
		} else if (randnum == 1) {
			cell = gb.getCell(cellx+1, celly);
		} else if (randnum == 2) {
			cell = gb.getCell(cellx, celly+1);
		} else if (randnum == 3) {
			cell = gb.getCell(cellx-1, celly);
		} else if (randnum == 4) {
			cell = gb.getCell(cellx, celly-1);
		} else if (randnum == 5) {
			cell = gb.getCell(cellx+1, celly+1);
		} else if (randnum == 6) {
			cell = gb.getCell(cellx-1, celly-1);
		} else if (randnum == 7) {
			cell = gb.getCell(cellx+1, celly-1);
		}
		if (checkloc(cell, '.')) return cell;
	}
}


bool Game::checkloc(shared_ptr<Cell> loc, char kind) {
	return loc->getState() == kind;
}


bool Game::missAtk() {
	return rand() % 2 == 0;
}


int Game::attack(shared_ptr<Cell> attackercell, shared_ptr<Cell> defendercell) {
	auto attacker = attackercell->getChar();
	auto defender = defendercell->getChar();
	string defendername = defender->getName();
	int damage = defender->beStruckBy(attacker);
	if (defender->getHP() == 0) {

		auto i = enemies.begin();
		while(i != enemies.end())
		{
			if ((*i)->getX() == defendercell->getX() && (*i)->getY() == defendercell->getY())
			{
				enemies.erase(i);
				break;
			}

			i ++;
		}
		if (defendername == "Merchant") {
			defendercell->setState('G');
			auto mh = make_shared<MerchantHoard>();
			defendercell->setCell(CellType::Item, nullptr, mh);
		} else {
			defendercell->setState('.');
			defendercell->setCell(CellType::Tile, nullptr, nullptr);
		}
	}
	return damage;
}


void Game::use(shared_ptr<Hero> user, shared_ptr<Cell> itemcell) {
	auto item = itemcell->getItem();
	item->applyItem(user);
	itemcell->setState('.');
	itemcell->setCell(CellType::Tile, nullptr, nullptr);
}


shared_ptr<Cell> Game::generateLocation() {
	int chamber;
	int cell;
	do {
		chamber = rand() % chambers.size();
		cell = rand() % chambers[chamber].size();
	} while (chambers[chamber][cell]->getType() != CellType::Tile);
	return chambers[chamber][cell];
}


void Game::printStats(shared_ptr<Hero> pc, const string &action, int floor) {
	string spacing = "                                                  ";
	string race = pc->getName();
	int hp = pc->getHP();
	int gold = pc->getGold();
	int atk = pc->getAtk();
	int def = pc->getDef();
	cout << "Race: " << race << " Gold: ";
	if (race == "Orc") {
		if (gold % 2 == 0) {
			cout << gold / 2;
		} else {
			cout << gold/2 << ".5";
		}
	} else {
		cout << gold / 2;
	}
	cout << spacing << "Floor: " << floor << endl;
	cout << "HP: " << hp << endl;
	cout << "Atk: " << atk << endl;
	cout << "Def: " << def << endl;
	cout << action << endl;
}


void Game::move(shared_ptr<Cell> ori, shared_ptr<Cell> des)
{
	if (ori->getState() == '@')
	{
		playercell = des;
	}
	else if (ori->getType() == CellType::Character && ori->getState() != '@') {
		for (unsigned int i = 0; i < enemies.size(); ++i) {
			if (enemies[i] == ori) enemies[i] = des;
		}
	}

	if (des->getState() == 'G') {
		des->getItem()->applyItem(ori->getChar());
		des->setState( '.');
		des->setCell(CellType::Tile, nullptr, nullptr);
	}

	shared_ptr<Character> c = ori->getChar();	

	//transfer what the character is stepping on
	char temp = ori->getState();
	ori->setState(c->getLoc());
	c->setLoc(des->getState());
	des->setState(temp);

	ori->setCell(des->getType(), nullptr, nullptr);

	des->setCell(CellType::Character, c, nullptr);

}

// returns the chamber number of the cell c or -1 if not found
int Game::member(shared_ptr<Cell> target)
{

	const int NUM_CHAMBERS = chambers.size();

	for (int c = 0; c < NUM_CHAMBERS; c++)
	{
		const	int NUM_FLOOR = chambers[c].size();

		for (int i = 0; i < NUM_FLOOR; i++)
		{

			if (chambers[c][i]->getX() == target->getX() && chambers[c][i]->getY() == target->getY())
			{
				return c;
			}
		}
	}
	return -1;
}


void Game::makeChambers() {
	const int NUM_CHAMBERS = 5;
	for (int i = 0; i < NUM_CHAMBERS; i++) {
		bool found = false;
		vector<shared_ptr<Cell>> p{};

		// find a cell not in a chamber
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < columns; c++) {
				if (gb.getCell(c,r)->getType() == CellType::Tile && member(gb.getCell(c,r)) < 0) {
					addChamber(c,r,p);
					found = true;
					break;
				}

			}
			if (found) break;
		}
		chambers.emplace_back(p);
	}
}


//add the tile and its neighbouring tiles  into the chamber			
void Game::addChamber(int row, int col, vector<shared_ptr<Cell>>& cham)
{

	if (row >= 0 && col >= 0 && row < columns && col < rows && gb.getCell(row,col)->getType() == CellType::Tile
			&& (!find_vec( gb.getCell(row,col), cham)) && member(gb.getCell(row,col)) < 0)
	{
		cham.emplace_back(gb.getCell(row,col));
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				addChamber(row + i,col + j ,cham);
			}
		}
	}
}


void Game::generateElements()
{
	//enemy probabilities
	const int NUM_ENEMIES = 20;
	const int ENEMYPROB = 18;
	const char WEREWOLF = 'W';
	const char VAMPIRE = 'V';
	const char GOBLIN = 'N';
	const char TROLL = 'T';
	const char PHOENIX = 'X';
	const char MERCHANT = 'M';

	char enemygen[] = {WEREWOLF,WEREWOLF,WEREWOLF,WEREWOLF,VAMPIRE,
		VAMPIRE,VAMPIRE,GOBLIN,GOBLIN,GOBLIN,
		GOBLIN,GOBLIN, TROLL, TROLL, PHOENIX,
		PHOENIX, MERCHANT,MERCHANT};	
	//potions
	const int NUM_POTIONS = 10;
	const int POTIONPROB = 6;
	const int RH = 0;
	const int BA = 1;
	const int BD = 2;
	const int PH = 3;
	const int WA = 4;
	const int WD = 5;

	//money
	const int NUM_GOLD = 10;
	const int GOLDPROB = 8;
	const char NORMAL = 'N';
	const char DRAGON = 'D';
	const char SMALL = 'S';
	char goldgen[] = {NORMAL,NORMAL,NORMAL,NORMAL,NORMAL,DRAGON,SMALL,SMALL};
	for (int p = 0; p < NUM_POTIONS; p++)
	{
		int pot = rand() % POTIONPROB;
		auto c = this->generateLocation();
		c->setState('P');

		if (pot == RH)
		{
			c->setCell(CellType::Item, nullptr, make_shared<RestoreHP>());			 
		}
		else if (pot == BA)
		{
			c->setCell(CellType::Item, nullptr, make_shared<BoostAtk>());
		}
		else if (pot == BD)
		{
			c->setCell(CellType::Item, nullptr, make_shared<BoostDef>());
		}
		else if (pot == PH)
		{
			c->setCell(CellType::Item, nullptr, make_shared<PoisonHP>());
		}
		else if(pot == WA)
		{
			c->setCell(CellType::Item,nullptr, make_shared<WoundAtk>());
		}
		else if(pot == WD)
		{
			c->setCell(CellType::Item, nullptr, make_shared<WoundDef>());
		}
	}
	//gold
	for (int i = 0; i < NUM_GOLD; i++)
	{
		char g = goldgen[rand() % GOLDPROB];
		auto gold = this->generateLocation();
		gold->setState('G');		
		if (g == NORMAL)
		{
			gold->setCell(CellType::Item,nullptr, make_shared<Normal>());
		}
		else if (g == SMALL)
		{
			gold->setCell(CellType::Item,nullptr, make_shared<SmallHorde>()) ;
		}
		else if (g == DRAGON)
		{
			while (!checksurr(gold,'.'))
			{
				gold = this->generateLocation();
			}
			gold->setCell(CellType::Item,nullptr, make_shared<DragonHoard>());
			auto dragonloc = gensurr(gold);
			dragonloc->setState('D');
			dragonloc->setCell(CellType::Character, make_shared<Dragon>(gold), nullptr);
		}
	}
	//generate enemies
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		char e = enemygen[rand() % ENEMYPROB];
		auto enem = this->generateLocation();
		enem->setState(e);		
		if (e == WEREWOLF)
		{
			enem->setCell(CellType::Character, make_shared<Werewolf>(), nullptr);
		}
		else if ( e == VAMPIRE)
		{
			enem->setCell(CellType::Character, make_shared<Vampire>(), nullptr);
		}
		else if (e == GOBLIN)
		{
			enem->setCell(CellType::Character, make_shared<Goblin>(), nullptr);
		}
		else if (e == TROLL)
		{
			enem->setCell(CellType::Character, make_shared<Troll>(),nullptr);
		}
		else if (e == PHOENIX)
		{
			enem->setCell(CellType::Character, make_shared<Phoenix>(),nullptr);
		}
		else if(e == MERCHANT)
		{
			enem->setCell(CellType::Character, make_shared<Merchant>(),nullptr);
		}
	}


}


void Game::initializeEnemies()
{
	for (int x = 0; x < columns; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			auto cell = gb.getCell(x,y);
			if (cell->getType() == CellType::Character && 
					cell->getState() != '@')
			{

				if (cell->getChar()->getName() == "Dragon") {
					auto dragon = dynamic_pointer_cast<Dragon>(cell->getChar());
					shared_ptr<Cell> potcell;
					for (int i = -1; i <= 1; i++)
					{
						for (int j = -1; j <= 1; j++)
						{
							potcell = gb.getCell(x+i, y+j);
							if ( potcell->getType() == CellType::Item &&
									potcell->getItem()->getName() == "Dragon Hoard")
							{
								dragon->setHoard(potcell);
							}
						}
					}
				}

				enemies.emplace_back(gb.getCell(x,y));
			}
		}
	}
}


void Game::playGame(string filename) {
	string userin;
	shared_ptr<Hero> player = nullptr;

	// Constant Messages:
	const string WELCOME = "Welcome to CC3k!";
	const string CHOOSERACE = "Please select one of the following races: ";
	const string RACES = "h = Human, d = Dwarf, e = Elf, o = Orc";
	const string INVALID = "Invalid command.";
	const string COMMANDS = "Commands:\nMove Directions: no, so, ea, we, ne, nw, se, sw\n\
Using potions: u <direction>\n\
Attacking enemies: a <direction>\n\
Quit: q\n\
Restart: r";
	const string REQUESTINPUT = "Please enter a command: ";
	const string WIN = "Congratulation! You win!";
	const string GAMEOVER = "Game over.";
	const string AGAIN = "Would you like to play again? (Y/N): ";

	while (true) {

		// Initializing Character:
		cout << WELCOME << " " << CHOOSERACE << endl << RACES << endl;
		while (cin >> userin) {
			if (userin == "h") {
				player = make_shared<Human>();
				break;
			} else if (userin == "e") {
				player = make_shared<Elf>();
				break;
			} else if (userin == "d") {
				player = make_shared<Dwarf>();
				break;
			} else if (userin == "o") {
				player = make_shared<Orc>();
				break;
			} else if (userin == "q") {
				return;
			} else {
				cout << INVALID << endl;
			}
		}
		if (!player) return;

		// Initializing GameBoard:
		int floor = 1;
		ifstream file{filename};
		gb.initialize(file, player);
		makeChambers();
		if (defaultmap) {
			// Generate player location:
			playercell = generateLocation();
			playercell->setState('@');
			playercell->setCell(CellType::Character, player, nullptr);
			// Generate stairs location:
			int pcchamber = -1;
			int count = 0;
			int chambersize = chambers.size();
			while (pcchamber == -1 && count < chambersize) {
				if (find_vec(playercell, chambers[count])) {
					pcchamber = count;
				}
				count++;
			}
			int randnum;
			do {
				randnum = rand() % chambersize;
			} while (randnum == pcchamber);

			int stairpos;
			do 
			{
				stairpos = rand() % chambers[randnum].size();
			} while (chambers[randnum][stairpos]->getType() != CellType::Tile);

			chambers[randnum][stairpos]->setState('\\');
			chambers[randnum][stairpos]->setCell(CellType::Stairs, nullptr, nullptr);
			// Generate everything;
			generateElements();

		} else {
			playercell = gb.getPlayerCell();
		}
		initializeEnemies();
		cout << COMMANDS << endl;
		cout << gb;
		printStats(player, "Action: Player character has spawned.", floor);

		// Turn Loop:
		while (true) {
			bool validmove = false;
			string action = "Action:";
			cout << REQUESTINPUT;
			if (!(cin >> userin)) return;
			int playerx = playercell->getX();
			int playery = playercell->getY();

			// Movement Commands:
			if (userin == "no" || userin == "so" || userin == "ea" || userin == "we" ||
					userin == "ne" || userin == "nw" || userin == "se" || userin == "sw") {
				shared_ptr<Cell> targetcell;
				string newaction;
				if (userin == "no") {
					targetcell = gb.getCell(playerx, playery-1);
					newaction = " PC moves North.";
				} else if (userin == "so") {
					targetcell = gb.getCell(playerx, playery+1);
					newaction = " PC moves South.";
				} else if (userin == "ea") {
					targetcell = gb.getCell(playerx+1, playery);
					newaction = " PC moves East.";
				} else if (userin == "we") {
					targetcell = gb.getCell(playerx-1, playery);
					newaction = " PC moves West.";
				} else if (userin == "ne") {
					targetcell = gb.getCell(playerx+1, playery-1);
					newaction = " PC moves Northeast.";
				} else if (userin == "nw") {
					targetcell = gb.getCell(playerx-1, playery-1);
					newaction = " PC moves Northwest.";
				} else if (userin == "se") {
					targetcell = gb.getCell(playerx+1, playery+1);
					newaction = " PC moves Southeast.";
				} else if (userin == "sw") {
					targetcell = gb.getCell(playerx-1, playery+1);
					newaction = " PC moves Southwest.";
				}
				if ((checkloc(targetcell, '.') || checkloc(targetcell, '#') ||
							checkloc(targetcell, 'G') || checkloc(targetcell, '+')) &&
						(!checkloc(targetcell, 'G') || (checkloc(targetcell, 'G') && targetcell->getItem()->getName() != "Dragon Hoard")
						 || (checkloc(targetcell, 'G') && targetcell->getItem()->getName() == "Dragon Hoard" &&
							 dynamic_pointer_cast<DragonHoard>(targetcell->getItem())->getStep()))) {
					move(playercell, targetcell);
					action += newaction;
					validmove = true;
					if (checksurr(playercell, 'P')) action += " PC sees an unknown potion.";
					// Player has reached stairs:
				} else if (checkloc(targetcell, '\\')) {
					if (floor == maxfloor) {
						string score;
						int finalgold = player->getGold();
						if (player->getName() == "Human") {
							score = to_string((finalgold * 3) / 4);
						} else if (player->getName() == "Orc" && finalgold % 2 != 0) {
							score = to_string(finalgold / 2) + ".5";
						} else {
							score = to_string(finalgold / 2);
						}
						cout << WIN << endl << "Your final score is: " << score << ". " << AGAIN;
						if ((cin >> userin) && (userin == "Y" || userin == "y")) {
							enemies.clear();
							chambers.clear();
							break;
						} else {
							return;
						}
					}
					++floor;
					gb.clearMap();
					int curgold = player->getGold();
					int curhpdiff = player->getHP() - player->getMaxHP();
					string currace = player->getName();
					if (currace == "Human") {
						player = make_shared<Human>();
					} else if (currace == "Elf") {
						player = make_shared<Elf>();
					} else if (currace == "Dwarf") {
						player = make_shared<Dwarf>();
					} else if (currace == "Orc") {
						player = make_shared<Orc>();
					}
					player->changeGold(curgold);
					player->changeHP(curhpdiff);
					gb.initialize(file, player);
					enemies.clear();
					chambers.clear();
					makeChambers();
					if (defaultmap) {
						// Generate player location:
						playercell = generateLocation();
						playercell->setState('@');
						playercell->setCell(CellType::Character, player, nullptr);
						// Generate stairs location:
						int pcchamber = -1;
						int count = 0;
						int chambersize = chambers.size();
						while (pcchamber == -1 && count < chambersize) {
							if (find_vec(playercell, chambers[count])) {
								pcchamber = count;
							}
							count++;
						}
						int randnum;
						do {
							randnum = rand() % chambersize;
						} while (randnum == pcchamber);

						int stairpos;
						do 
						{
							stairpos = rand() % chambers[randnum].size();
						} while (chambers[randnum][stairpos]->getType() != CellType::Tile);

						chambers[randnum][stairpos]->setState('\\');
						chambers[randnum][stairpos]->setCell(CellType::Stairs, nullptr, nullptr);

						// Generate elements:
						generateElements();
						initializeEnemies();

					} else {

						playercell = gb.getPlayerCell();
						initializeEnemies();
					}
					action = action + " Player has moved to floor " + to_string(floor) + ".";
				}	else {
					action = action + " " + INVALID;
				}

				// Use Commands:
			} else if (userin == "u") {
				string dir;
				if (!(cin >> dir)) return;
				if (dir == "no" || dir == "so" || dir == "ea" || dir == "we" ||
						dir == "ne" || dir == "nw" || dir == "se" || dir == "sw") {
					shared_ptr<Cell> targetcell;
					if (dir == "no") {
						targetcell = gb.getCell(playerx, playery-1);
					} else if (dir == "so") {
						targetcell = gb.getCell(playerx, playery+1);
					} else if (dir == "ea") {
						targetcell = gb.getCell(playerx+1, playery); 
					} else if (dir == "we") {
						targetcell = gb.getCell(playerx-1, playery);
					} else if (dir == "ne") {
						targetcell = gb.getCell(playerx+1, playery-1);
					} else if (dir == "nw") {
						targetcell = gb.getCell(playerx-1, playery-1);
					} else if (dir == "se") {
						targetcell = gb.getCell(playerx+1, playery+1);
					} else if (dir == "sw") {
						targetcell = gb.getCell(playerx-1, playery+1);
					}
					if (checkloc(targetcell, 'P')) {
						auto item = targetcell->getItem();
						string itemname = item->getName();
						use(player, targetcell);
						action = action + " PC uses " + itemname + ".";
						move(playercell, targetcell);
						validmove = true;
					} else action = action + " " + INVALID;
				}	else {
					action = action + " " + INVALID;
				}

				// Attack Commands:
			} else if (userin == "a") {
				string dir;
				if (!(cin >> dir)) return;
				if (dir == "no" || dir == "so" || dir == "ea" || dir == "we" ||
						dir == "ne" || dir == "nw" || dir == "se" || dir == "sw") {
					shared_ptr<Cell> targetcell;
					if (dir == "no") {
						targetcell = gb.getCell(playerx, playery-1);
					} else if (dir == "so") {
						targetcell = gb.getCell(playerx, playery+1);
					} else if (dir == "ea") {
						targetcell = gb.getCell(playerx+1, playery); 
					} else if (dir == "we") {
						targetcell = gb.getCell(playerx-1, playery);
					} else if (dir == "ne") {
						targetcell = gb.getCell(playerx+1, playery-1);
					} else if (dir == "nw") {
						targetcell = gb.getCell(playerx-1, playery-1);
					} else if (dir == "se") {
						targetcell = gb.getCell(playerx+1, playery+1);
					} else if (dir == "sw") {
						targetcell = gb.getCell(playerx-1, playery+1);
					}
					if (targetcell->getType() == CellType::Character) {
						string newhp;
						auto enemy = targetcell->getChar();
						string enemyname = enemy->getName();
						string damage = to_string(attack(playercell, targetcell));
						if (targetcell->getChar()) {
							newhp = to_string(enemy->getHP());
						} else {
							newhp = "0";
							if (enemyname != "Merchant" && enemyname != "Dragon") player->changeGold(player->getMult());
						}
						action = action + " PC deals " + damage + " damage to " + enemyname + " (" + newhp + " HP).";
						validmove = true;
					} else {
						action = action + " " + INVALID;
					}
				} else {
					action = action + " " + INVALID;
				}
			} else if (userin == "r") {
				chambers.clear();
				enemies.clear();
				break;
			} else if (userin == "q") {
				return;
			}
			// Enemy's Turn:
			if (validmove) {
				for (unsigned int i = 0; i < enemies.size(); ++i) {
					auto target = checksurr(enemies[i], '@');
					char enemytype = enemies[i]->getState();
					shared_ptr<Merchant> mp = nullptr;
					if (enemytype == 'D') {
						shared_ptr<Dragon> dp = dynamic_pointer_cast<Dragon>(enemies[i]->getChar());
						if (!checksurr(dp->getHoard(), '@')) continue;
					}
					if (enemytype == 'M') mp = dynamic_pointer_cast<Merchant>(enemies[i]->getChar());
					if (enemytype == 'D' || (target && enemytype != 'M') || (target && enemytype == 'M' && mp->getAggro())) {
						auto attacker = enemies[i]->getChar();
						string attackername = attacker->getName();
						if (!missAtk()) {
							string damage;
							if (enemytype == 'D') {
								damage = to_string(attack(enemies[i], playercell));
							} else {
								damage = to_string(attack(enemies[i], target));
							}
							action = action + " " + attackername + " deals " + damage + " damage to PC.";
							if (player->getHP() == 0) break;
						} else {
							action = action + " " + attackername + " attacks PC but misses."; 
						}
					} else {
						auto targloc = gensurr(enemies[i]);
						move(enemies[i], targloc);
					}
				}
				sortEnemies();
			}
			cout << gb;
			printStats(player, action, floor);
			if (player->getHP() == 0) {
				cout << GAMEOVER << endl << AGAIN;
				if ((cin >> userin) && (userin == "Y" || userin == "y")) {
					chambers.clear();
					enemies.clear();
					break;
				} else {
					return;
				}
			}
		}
	}
}

