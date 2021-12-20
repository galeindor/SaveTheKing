#include "Controller.h"
#include <iostream>
#include <fstream>
#include <string>
#include "io.h"

int main()
{
	// open the file contains file levels
	std::ifstream levels;
	levels.open("levelList.txt");

	if (!levels)
		std::cerr << "Failed to open file!\n";

	// read and open levels one by one, changes level when finished
	std::string line;
	while (std::getline(levels, line))
	{
		auto gameController = Controller(line);
		gameController.run();
	}
	levels.close();
	return EXIT_SUCCESS;
}