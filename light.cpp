#include "light.hpp"

Light::Light(GLuint programm) {
	this->programm = programm;
}

void Light::draw() {
	glm::vec3 ambientColor = glm::vec3(1.0f, 0.0f, 0.0f); //Color (0.2, 0.2, 0.2)
	glm::vec3 lightColor0 = glm::vec3(0.5f, 0.5f, 0.5f);

	glm::vec3 lightPos0 =glm::vec3(-4.0f, 0.0f, 8.0f); //Positioned at (4, 0, 8)

	glm::vec3 lightColor1 = glm::vec3(0.5f, 0.2f, 0.2f); //Color (0.5, 0.2, 0.2)
	glm::vec3 lightPos1 = glm::vec3(-1.0f, 0.5f, 0.5f);

	glm::vec3 lightdir = glm::vec3(1.0f,1.0f,0.0f);
	glUseProgram(programm);

	GLuint ambientID = glGetUniformLocation(programm, "ambient");
	glUniform3fv(ambientID, 1, glm::value_ptr(ambientColor));

	GLuint lightColorID = glGetUniformLocation(programm, "spotcolor");
	glUniform3fv(lightColorID, 1, glm::value_ptr(lightColor0));

	GLuint spotPosID = glGetUniformLocation(programm, "spotpos");
	glUniform3fv(spotPosID, 1, glm::value_ptr(lightPos0));

	GLuint lightDirID = glGetUniformLocation(programm, "lightdir");
	glUniform3fv(lightDirID, 1, glm::value_ptr(lightPos0));
}
