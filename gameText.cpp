#include "gameText.h"
#include "utils.h"
#include <cstring>

GameText::GameText(const std::string &name, GLuint &programm, std::vector<float> &offset, const char* police, const char* text) : GameObject(name,programm,offset) {
	this->police = std::string(police);
	this->text = std::string(text);
	textureID = loadDDS(police);
	x = 50;
	y = 50;
	size = 30;

	// text2DShaderID = loadShaders("text2D.v.glsl", "text2D.f.glsl");
	// text2DUniformID = glGetUniformLocation(text2DShaderID, "textTexture");
}

void GameText::makeObject() {
	unsigned int length = text.size();
	for(unsigned int i=0; i<length; i++) {
		Vertex tmp;

		tmp.addPosition(glm::vec3(x+i*size, y+size, 0));
		tmp.addPosition(glm::vec3(x+i*size, y, 0));
		tmp.addPosition(glm::vec3(x+i*size+size, y+size, 0));
		tmp.addPosition(glm::vec3(x+i*size+size, y, 0));
		tmp.addPosition(glm::vec3(x+i*size+size, y+size, 0));
		tmp.addPosition(glm::vec3(x+i*size, y, 0));

		char character = text[i];
		float uv_x = (character%16)/16.0f;
		float uv_y = (character/16)/16.0f;

		glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
		glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
		glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
		glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );

		tmp.addUv(uv_up_left, uv_down_left, uv_up_right);
		tmp.addUv(uv_down_right, uv_up_right, uv_down_left);
		vertexCount++;
	}

	GLuint positionBuffer;
	GLuint uvsBuffer;

	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount* 3 * sizeof(float), mesh.getPositions().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &uvsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvsBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount*2*sizeof(float), mesh.getUvs().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//---------------------------
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvsBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );
}

void GameText::draw() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// glUniform1i(text2DUniformID, 0);
	glDrawElementsInstanced(type, mesh.getIbos().size(), GL_UNSIGNED_INT, 0,offset.size()/3);

	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

GameText::~GameText() {

}
