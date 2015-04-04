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
		GameCube(const std::string name,GLuint programm,std::vector<glm::vec3> offset,const std::string &nameTexture, int width, int height, bool isDynamic=false );

	private:
		int width;
		int height;
		std::string textureName;
};

#endif
