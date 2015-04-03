#include "skybox.h"
#include "utils.h"

Skybox::Skybox(std::string top, std::string bottom, std::string left, std::string right, std::string front, std::string back) {
	_faces.push_back(top);
	_faces.push_back(bottom);
	_faces.push_back(left);
	_faces.push_back(right);
	_faces.push_back(front);
	_faces.push_back(back);
}

void Skybox::loadCubemap() {
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);

	int width,height;
	GLuint image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for(int i = 0; i < _faces.size(); i++) {
		image = loadTGATexture(_faces[i]); 
		// TODO
		// glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}  

