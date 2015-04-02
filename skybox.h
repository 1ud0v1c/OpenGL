#ifndef SKYBOX_H
#define SKYBOX_H

#include "gameObject.h"
#include "mesh.h"
#include "utils.h"
#include <array>

class SkyBox: public GameObject {
	public:
		void draw();
		void makeObject();
		SkyBox(const std::string name,GLuint programm,std::vector<float> offset,const std::string &nameTexture, int width, int height );

	private:
		int width;
		int height;
		std::string textureName;

};

#endif
