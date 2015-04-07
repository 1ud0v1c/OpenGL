#ifndef GAME_TEXT_H
#define GAME_TEXT_H

#include "gameObject.h"

class GameText : public GameObject {
	public:
		GameText(const std::string &name, GLuint &programm, std::vector<glm::vec3> &offset, const char* police, const char* text, int x, int y, int size); 
		~GameText();
		GLuint getProgramm();
		void makeObject();
		void draw();
		void update(float dt);
		void update(int lifes);
		void update(double score);
		void setText(std::string text);

	protected:
		std::string police;
		std::string text;
		int x;
		int y;
		int size;
		int i = 0;
		float deltaTime=0; 
		unsigned int text2DUniformID;
		unsigned int positionBuffer;
		unsigned int uvsBuffer;

		std::vector<glm::vec2> vertices;
		std::vector<glm::vec2> UVs;
};

#endif
