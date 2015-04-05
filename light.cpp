#include "light.h"

Light::Light() {
}

Light::Light(GLuint programm) {
	this->programm = programm;
}

void Light::update(glm::vec3 pos) {

	ambientColor = glm::vec3(0.2f, 0.2f, 0.2f); //Color (0.2, 0.2, 0.2)
	lightColor0 = glm::vec3(0.2f, 0.2f, 0.2f);

	lightPos0 =  glm::vec3(0.0f, 0.0f, 0.0f); //Positioned at (4, 0, 8)

	lightColor1 = glm::vec3(0.5f, 0.2f, 0.2f); //Color (0.5, 0.2, 0.2)
	lightPos1 = glm::vec3(-1.0f, 0.5f, 0.5f);

	lightdir = glm::vec3(1.0f,0.0f,0.0f);
}

void Light::draw() {
	glUseProgram(programm);

	GLuint ambientID = glGetUniformLocation(programm, "ambient");
	glUniform3fv(ambientID, 1, glm::value_ptr(ambientColor));

	GLuint lightColorID = glGetUniformLocation(programm, "lightcolor");
	glUniform3fv(lightColorID, 1, glm::value_ptr(lightColor0));

	GLuint spotPosID = glGetUniformLocation(programm, "spotpos");
	glUniform3fv(spotPosID, 1, glm::value_ptr(lightPos0));

	GLuint lightDirID = glGetUniformLocation(programm, "lightdir");
	glUniform3fv(lightDirID, 1, glm::value_ptr(lightdir));

	glUseProgram(0);
}
