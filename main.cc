#include "game.h"
#include <fstream>
#include <cstdlib>
using namespace std;


int main(int argc, char *argv[]) {
	srand(time(NULL));
	string filename = "DefaultMap.txt";
	Game g;
	if (argc == 2) {
		filename = argv[1];
		g.defaultmap = false;
	}
	g.playGame(filename);
}

