#ifndef HUD_H
#define HUD_H

#include <iostream>
#include <map>
#include "gameText.h"

class HUD {
	public:
		HUD();
		HUD(std::map<std::string,GLuint> programms);
		void init(); 
		void update(float dt);
		void draw();

	protected:
		GameText *text;
		std::map<std::string,GLuint> programms;

};

#endif
