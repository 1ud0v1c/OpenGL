#include "gameObject.h"

GameObject::GameObject(const std::string &name,GLuint &programm,std::vector<float> &offset) {
	_name = name;
	this->programm = programm;
	type = GL_TRIANGLES;
	this->offset = offset;
}

void GameObject::setUnit(int unit) {
	this->unit = unit;
}
GLuint GameObject::getProgramm() {
	return programm;
}

void GameObject::makeObject() {
	GLuint positionBuffer;
	GLuint indexBuffer;
	GLuint colorBuffer;
	GLuint textureBuffer;
	GLuint instanceVBO;

	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * offset.size(), offset.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount* 3 * sizeof(float), mesh.getPositions().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * 4 * sizeof(float), mesh.getColors().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexCount*6*sizeof(unsigned int), mesh.getIbos().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, &textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount*2*sizeof(float), mesh.getUvs().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//--------- Encapsulation and setting of VBOs
	//
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	GLint positionIndex = glGetAttribLocation(programm, "position");
	glEnableVertexAttribArray(positionIndex);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	GLint normalIndex = glGetAttribLocation(programm, "color");
	glEnableVertexAttribArray(normalIndex);
	glVertexAttribPointer(normalIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	GLint textureIndex = glGetAttribLocation(programm, "vertexUv");
	glEnableVertexAttribArray(textureIndex);
	glVertexAttribPointer(textureIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//--------- Encapsulation of an IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glEnableVertexAttribArray(6);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(6, 1);
	glBindVertexArray(0);
}

std::string GameObject::getName() {
	return _name;
}

void GameObject::setType(GLuint type) {
	this->type = type;
}

void GameObject::draw() {
	GLfloat fLargest;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
	glUniform1i(textureID, 0);

	glBindVertexArray(vao);
	glDrawElementsInstanced(type, mesh.getIbos().size(), GL_UNSIGNED_INT, 0,offset.size()/3);
	glBindVertexArray(0);
}

GameObject::~GameObject() { }
