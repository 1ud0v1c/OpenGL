#ifndef GAME_TEXT_H
#define GAME_TEXT_H

#include "gameObject.h"

class GameText : public GameObject {
	public:
		GameText(const std::string &name, GLuint &programm, std::vector<float> &offset, const char* police, const char* text); 
		~GameText();
		GLuint getProgramm();
		void makeObject();
		void draw();

	protected:
		std::string police;
		std::string text;
		int x;
		int y;
		int size;
		int i = 0;
		unsigned int text2DUniformID;
		unsigned int positionBuffer;
		unsigned int uvsBuffer;

		std::vector<glm::vec2> vertices;
		std::vector<glm::vec2> UVs;
};

#endif
