#ifndef GAME_CUBE_H
#define GAME_CUBE_H

#include "gameObject.h"
#include "mesh.h"
#include "utils.h"
#include <array>

class GameCube : public GameObject {
	public:
		void draw();
		void makeObject();
		GameCube(const std::string name,GLuint programm,std::vector<float> offset,const std::string &nameTexture, int width, int height );

	private:
		int width;
		int height;
		std::string textureName;
};

#endif
