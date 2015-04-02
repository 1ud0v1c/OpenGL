#include "skybox.h"


SkyBox::SkyBox(const std::string name,GLuint programm,std::vector<float> offset,const std::string &nameTexture, int width, int height ):
	GameObject(name,programm,offset)
{
	this->width = width;
	this->height = height;
	this->textureName = nameTexture;

}


void SkyBox::makeObject() {

	std::cout << "make Cube" <<std::endl;
	const float vertices[] = {

		-1.0, -1.0,  1.0,
		1.0, -1.0,  1.0,
		1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
		// back
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0

	};

	const unsigned int indexTab[] = {
		0, 1, 2,
		2, 3, 0,
		// top
		3, 2, 6,
		6, 7, 3,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// left
		4, 0, 3,
		3, 7, 4,
		// right
		1, 5, 6,
		6, 2, 1
	};

	const float uvTab[] = {
		0,0,1,0,1,1,0,0,1,1,0,1
	};


	for(int i=0;i<36;i++)
		mesh.addIbo(indexTab[i]);

	std::array<Vertex,8> v;
	for(int i=0;i<8;i++) {
		v[i].addPosition(glm::vec3(vertices[i*3],vertices[i*3+1],vertices[i*3+2]));
		v[i].addNormal(glm::vec3(1,1,1));
		v[i].addColor(0.5,0.5,0.5,1);

	}
	for(int i=0;i<6;i++) {
		v[i].addUv(glm::vec2(uvTab[0],uvTab[1]),glm::vec2(uvTab[2],uvTab[3]),glm::vec2(uvTab[4],uvTab[5]));
		v[i].addUv(glm::vec2(uvTab[6],uvTab[7]),glm::vec2(uvTab[8],uvTab[9]),glm::vec2(uvTab[10],uvTab[11]));
	}


	textureID =glGetUniformLocation(programm, "colormap"); 

	texture = loadTGATexture(textureName);

	for(auto &ve :v ) {
		mesh.addVertex(ve);
	}

	GameObject::makeObject();
}

void SkyBox::draw() {

	GameObject::draw();

}
