#include "skybox.h"
#include "utils.h"

Skybox::Skybox() {}

Skybox::Skybox(GLuint program, std::string top, std::string bottom, std::string left, std::string right, std::string front, std::string back) {
	this->program = program;
	_faces.push_back(top);
	_faces.push_back(bottom);
	_faces.push_back(left);
	_faces.push_back(right);
	_faces.push_back(front);
	_faces.push_back(back);
}

void Skybox::loadCubemap() {
	int width = 256, height = 256;
	char* image; 

	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for(int i = 0; i < _faces.size(); i++) {
		image = read_tga(_faces[i].c_str(), width, height); 
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


void Skybox::update(glm::vec3 position) {

	glUseProgram(program);
	GLuint positionBuffer;
	GLuint loc =glGetUniformLocation(program, "offset");
	glUniform3f(loc,position[0],position[1],position[2]);

	glUseProgram(0);

}

void Skybox::init() {
	glUseProgram(program);
	loadCubemap();

	GLfloat skyboxVertices[] = {
		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,

		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,

		SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,

		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,

		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,

		-SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE
	};

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	glUseProgram(0);
}

void Skybox::draw() {
	glUseProgram(program);

	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	unsigned int skyID = glGetUniformLocation(program, "skybox");
	glUniform1i(skyID, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);

	glUseProgram(0);
}

GLuint Skybox::getProgramm() {
	return program;
}

