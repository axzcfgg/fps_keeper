#include "FpsKeeper.hpp"
#include <iostream>


// you have to define macro WIN_BUILD or LINUX_BUILD
int main(int argc, char *argv[]) {
	// default is 60fps
	fps::keeper fps;

	// now 1fps = do something per second
	fps.set_fps(1); 
	while(true) {

		// something do here
		std::cout << "time" << std::endl;

		// this function keeps fps you set.
		fps.wait();
	}
	return 0;
}
