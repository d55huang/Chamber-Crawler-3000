# CC3k

CC3k is a terminal-based rouge-like game consisting of a board 79 columns wide and 30 rows high. The player character moves through a dungeon and slays enemies and collects treasure until reaching the end of the dungeon (on the 5th floor). A dungeon consists of different floors which consist of chambers connected with passages.

## Player Character

By default, the player character is a human. The player has the option of changing their race to something more fantastical. The options include dwarf, elf, and orc.

* Human	(140 HP, 20 Atk, 20 Def)
* Dwarf	(100 HP, 20 Atk, 30 Def) [Gold is doubled in value.]
* Elf		(140 HP, 30 Atk, 10 Def) [Negative potions have positive effect.]
* Orc		(180 HP, 30 Atk, 25 Def) [Gold is half in value.]

## Commands

* no, so, ea, we, ne, nw, se, sw: moves the player character one block in the appropriate cardinal direction
* u \<direction\>: uses the potion indicated by the direction (e.g. no, so, ea)
* a \<direction\>: attacks the enemy in the specified direction, if the monster is in the immediately specified block
* h, e, d, o: species the race the player wishes to be when starting a game
* r: restarts the game. All stats, inventory, and gold are reset. A new race should be selected.
* q: allows the player to admit defeat and exit the game.

## Enemies

Enemies are the mortal foes of the player character. The enemies in the game and their denotations are as follows:

* Vampire (V)		(50 HP, 25 Atk, 25 Def)
* Werewolf (W)	(120 HP, 30 Atk, 5 Def)
* Troll (T)		(120 HP, 25 Atk, 15 Def)
* Goblin (N)		(70 HP, 5 Atk, 10 Def)
* Merchant (M) 	(30 HP, 70 Atk, 5 Def)
* Dragon (D)		(150 HP, 20 Atk, 20 Def)
* Phoenix (X)	(50 HP, 35 Atk, 20 Def)

Merchants can be attacked and slain by the player character. Attacking or slaying a Merchant will cause every Merchant from that point forward to become hostile to the player character.

Dragons always spawn in a one block radius of its dragon horde pile of treasure (see Treasure). That is, if a dragon horde is spawned then a dragon is spawned.

## Items

In CC3k, there is only one type of usable item: a potion. Potions are of two types: positive and negative. Potions can provide the player character with positive and negative bonuses as outlined below. All potions are denoted on the map with a P. The effects of a potion are not known until it is used.

### Positive Potions

* Restore health (RH): restore up to 10 HP (cannot exceed maximum prescribed by race)
* Boost Atk (BA): increase ATK by 5
* Boost Def (BD): increase Def by 5

### Negative Potions

* Poison health (PH): lose up to 10 HP (cannot fall below 0 HP)
* Wound Atk (WA): decrease Atk by 5
* Wound Def (WD): decrease Def by 5

The effects of RH and PH are permanent while the effects of all other potions are limited to the floor they are used on. For example, using a BA potion will only boost the player character's Atk until the beginning of the next floor.

### Treasure

Treasure in CC3k consists only of gold. Gold can be in several types of piles: normal (value 1), small horde (value 2), merchant hoard (value 4), and dragon hoard (value 6). Thus, dragon must always protect a dragon hoard whenever it randomly spawns. A dragon horde can only be picked up once the dragon guarding it has been slain. Gold, regardless of type, is denoted by 'G' on the map. A merchant horde is dropped upon the death of a merchant.

## Customized Maps

CC3k supports custom layouts for the 5 floors of the dungeon. An optional single command line argument allows for a text file that specifies the layout of each of the 5 floors.  Note that potions and piles of gold will be denoted by numbers (outlined below) but will be converted to the appropriate character when displayed to the player. See DefaultMap.txt for an example.
The translation of numbers to items is as follows: 0 - RH, 1 - BA, 2 - BD, 3 - PH, 4 - WA, 5 - WD, 6 - normal gold pile, 7 - small horde, 8 - merchant horde, 9 - dragon horde.
