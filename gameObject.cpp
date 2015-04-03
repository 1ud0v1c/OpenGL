#include <algorithm>
#include "gameObject.h"

GameObject::GameObject(const std::string &name,GLuint &programm,std::vector<glm::vec3> &offset, const std::string &textureName) {
     _name = name;
     this->programm = programm;
     type = GL_TRIANGLES;
     this->offset = offset;
	 this->textureName = textureName;
}

void GameObject::setUnit(int unit) {
     this->unit = unit;
}


void  GameObject::moveObject(glm::vec3 position) {

	glUseProgram(programm);
	GLuint positionBuffer;
	GLuint loc =glGetUniformLocation(programm, "moveOffset");
	glUniform3f(loc,position[0],position[1],position[2]);

	glUseProgram(0);
}

GLuint GameObject::getProgramm() {
     return programm;
}

void GameObject::makeObject() {
	if(textureName.size() >2) {
		textureID = glGetUniformLocation(programm, "colormap");
		texture = loadTGATexture(textureName);
		std::cout << textureName << std::endl;
	}

	GLuint positionBuffer;
	GLuint indexBuffer;
	GLuint colorBuffer;
	GLuint normalBuffer;
	GLuint textureBuffer;
	GLuint instanceVBO;

	std::cout << offset[0][0] << std::endl;

	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * offset.size(), &offset[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.getPositions().size() * sizeof(glm::vec3), mesh.getPositions().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.getColors().size() * sizeof(glm::vec4), mesh.getColors().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.getNormals().size() * sizeof(glm::vec3), mesh.getNormals().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getIbos().size()*sizeof(unsigned int), mesh.getIbos().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, &textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.getUvs().size()*sizeof(glm::vec2), mesh.getUvs().data(), GL_STATIC_DRAW);
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
	GLint colorIndex = glGetAttribLocation(programm, "color");
	glEnableVertexAttribArray(colorIndex);
	glVertexAttribPointer(colorIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	GLint normalIndex = glGetAttribLocation(programm, "normal");
	glEnableVertexAttribArray(normalIndex);
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

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
	glDrawElementsInstanced(type, mesh.getIbos().size(), GL_UNSIGNED_INT, 0,offset.size());
	glBindVertexArray(0);
}

bool GameObject::isColliding(GameObject* go){
	glm::vec3 center = getCenter();
	glm::vec3 hitbox(radius+center.x, radius+center.y, radius+center.z);

	int other_radius = go->getRadius();
	glm::vec3 other_center = go->getCenter();
	glm::vec3 other_hitbox(other_radius-other_center.x, other_radius+other_center.y, other_radius-other_center.z);

	if (hitbox.x  >= other_hitbox.x){
		return true;
	}
	if (hitbox.z >= other_hitbox.z){
		return true;
	}
	return false;
}

glm::vec3 GameObject::getCenter(){
	glm::vec3 min;
	glm::vec3 max;
	std::vector<glm::vec3> positions = mesh.getPositions();
	min = getMinPosition(positions);
	max = getMaxPosition(positions);
	return glm::vec3( (min.x+max.x)/2, (min.y+max.y)/2, (min.z+max.z)/2); 
}

int GameObject::getRadius(){
	return radius;
}

GameObject::~GameObject() { }


bool GameObject::loadOBJ(const std::string  &path) {
	printf("Loading OBJ file %s...\n", path.c_str());

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	FILE * file = fopen(path.c_str(), "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		return false;
	}

	while(1) {
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) {
			break; 
		}

		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			uv.y = -uv.y; 
			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9){
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}else{
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	for(unsigned int i=0; i<vertexIndices.size(); i++){
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];

		Vertex v;
		v.addPosition(vertex);
		v.addUv(uv);
		v.addNormal(normal);
		v.addColor(1,1,1,0.5);
		mesh.addVertex(v);
	}

	for (int i = 0; i < mesh.getPositions().size(); i++) {
		mesh.addIbo(i);
	}
	return true;
}

