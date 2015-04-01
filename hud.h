#ifndef HUD_H
#define HUD_H

#include <iostream>
#include <map>
#include "gameText.h"
#include "level.h"

class HUD {
	public:
		HUD();
		HUD(std::map<std::string,GLuint> programms);
		void init(); 
		void update(Level &level, float dt);
		void draw();

	protected:
		GameText *chrono;
		GameText *lifes;
		Level level;
		std::map<std::string,GLuint> programms;

};

#endif
