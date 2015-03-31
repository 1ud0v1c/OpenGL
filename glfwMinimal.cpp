#include <iostream>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp> 
#include <glm/gtc/constants.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include "glfwMinimal.h"
#include "game.h"
int main(void) {
	Game game;
	game.init();
	game.run();
}


