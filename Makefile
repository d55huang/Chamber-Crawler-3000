CXX = g++-5
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
EXEC = cc3k
OBJECTS = main.o boostatk.o boostdef.o cell.o character.o dragon.o dragonhoard.o dwarf.o elf.o enemy.o game.o gameboard.o goblin.o hero.o human.o item.o merchant.o merchanthoard.o normal.o observer.o orc.o phoenix.o poisonhp.o potion.o restorehp.o smallhorde.o textdisplay.o treasure.o troll.o vampire.o werewolf.o woundatk.o wounddef.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
