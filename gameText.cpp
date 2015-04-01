#include "gameText.h"
#include "utils.h"
#include <cstring>


GameText::GameText(const std::string &name, GLuint &programm, std::vector<float> &offset, const char* police, const char* text) : GameObject(name,programm,offset) {
	this->police = std::string(police);
	this->text = std::string(text);
	textureID = loadDDS(police);
	x = 10;
	y = 500;
	size = 60;
}

GLuint GameText::getProgramm() {
	return programm;
}

void GameText::makeObject() {

}

void GameText::draw() {
	unsigned int length = text.size();

	for(unsigned int i=0; i<length; i++) {
		glm::vec2 vertex_up_left    = glm::vec2( x+i*size     , y+size );
		glm::vec2 vertex_up_right   = glm::vec2( x+i*size+size, y+size );
		glm::vec2 vertex_down_right = glm::vec2( x+i*size+size, y      );
		glm::vec2 vertex_down_left  = glm::vec2( x+i*size     , y      );

		vertices.push_back(vertex_up_left   );
		vertices.push_back(vertex_down_left );
		vertices.push_back(vertex_up_right  );

		vertices.push_back(vertex_down_right);
		vertices.push_back(vertex_up_right);
		vertices.push_back(vertex_down_left);

		char character = text[i];
		float uv_x = (character%16)/16.0f;
		float uv_y = (character/16)/16.0f;

		glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
		glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
		glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
		glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );
		UVs.push_back(uv_up_left   );
		UVs.push_back(uv_down_left );
		UVs.push_back(uv_up_right  );

		UVs.push_back(uv_down_right);
		UVs.push_back(uv_up_right);
		UVs.push_back(uv_down_left);

		// Vertex tmp;

		// tmp.addPosition(glm::vec3(x+i*size, y+size, 0));
		// tmp.addPosition(glm::vec3(x+i*size, y, 0));
		// tmp.addPosition(glm::vec3(x+i*size+size, y+size, 0));
		// tmp.addPosition(glm::vec3(x+i*size+size, y, 0));
		// tmp.addPosition(glm::vec3(x+i*size+size, y+size, 0));
		// tmp.addPosition(glm::vec3(x+i*size, y, 0));

		// char character = text[i];
		// float uv_x = (character%16)/16.0f;
		// float uv_y = (character/16)/16.0f;

		// glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
		// glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
		// glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
		// glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );

		// tmp.addUv(uv_down_right, uv_up_right, uv_down_left);
		// tmp.addUv(uv_up_left, uv_down_left, uv_up_right);

		// mesh.addVertex(tmp);
	}

	text2DUniformID = glGetUniformLocation(programm, "textTexture");
	// std::cout << "GameText >> makeObject() = text2DUniformID : " << text2DUniformID << std::endl;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvsBuffer);
	glBufferData(GL_ARRAY_BUFFER, UVs.size()*sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

	std::cout << "GameText >> draw() = text2DUniformID : " << text2DUniformID << ", programm : " << programm << std::endl;
	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(text2DUniformID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvsBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw call
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glDisable(GL_BLEND);
	glBindVertexArray(0);
}

GameText::~GameText() {

}
