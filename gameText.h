#ifndef GAME_TEXT_H
#define GAME_TEXT_H

#include "gameObject.h"

class GameText : public GameObject {
	public:
		GameText(const std::string &name, GLuint &programm, std::vector<float> &offset, const char* police, const char* text); 
		~GameText();
		void makeObject();
		void draw();

	protected:
		std::string police;
		std::string text;
		int x;
		int y;
		int size;

};

#endif
