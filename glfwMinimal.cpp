#include <iostream>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp> 
#include <glm/gtc/constants.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include "glfwMinimal.h"
#include "utils.h"
#include "camera.h"
#include "controls.h"
#include "text2D.h"

using namespace std;

GLuint programId;
GLuint vao;
unsigned int longueurIndex;
float uTime = 0.0;
GLFWwindow* window;
Camera *cam = new Camera();

int main(void) {
	int running = 1;
	float diff = 0.005;
	longueurIndex=0;

	init();
	Controls controls(window,cam,true);

	while(running){
		GLfloat currentFrame = glfwGetTime();
		running = controls.handleActions(currentFrame);
		controls.getCurrentFPS();
		renderFrame();

		if(uTime > 1) {
			diff = -diff;
		} else if(uTime < 0) {
			diff = -diff;
		}
		uTime += diff;
	}
	exit(0);
}


void make_resources(){
	int width, height;
	string tempv, tempf;
	GLint lengthv, lengthf;

	make_shaders(&tempv, &tempf, &lengthv, &lengthf);
	init_shaders(&tempv, &tempf, &lengthv, &lengthf, &programId);

	char* data = read_tga("../data/checkerboard.tga", width, height);

	GLuint textureID=0;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Texture
	Text2D text;
	GLuint TextureID = glGetUniformLocation(programId, "textTexture");
	text.initText2D("../data/ubuntu_regular_24.tga");

	// Création du tore
	int torusCount=50;
	GLuint positionToreBuffer;
	GLuint colorToreBuffer;
	GLuint indexToreBuffer;
	GLuint uvsBuffer;

	Mesh *mesh= new Mesh();
	makeATexturedTorus(mesh,1,0.25,torusCount);

	glGenBuffers(1, &positionToreBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionToreBuffer);
	glBufferData(GL_ARRAY_BUFFER, torusCount * torusCount * 3 * sizeof(float), mesh->getPositions().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &colorToreBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorToreBuffer);
	glBufferData(GL_ARRAY_BUFFER, torusCount * torusCount * 4 * sizeof(float), mesh->getColors().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexToreBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexToreBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, longueurIndex * sizeof(unsigned int), mesh->getIbos().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1,&uvsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvsBuffer);
	glBufferData(GL_ARRAY_BUFFER, longueurIndex * 2 * sizeof(unsigned int), mesh->getUvs().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, positionToreBuffer);

	GLint positionIndex = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(positionIndex);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, colorToreBuffer);
	GLint colorIndex = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(colorIndex);
	glVertexAttribPointer(colorIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER,uvsBuffer);
	GLint textIndex = glGetAttribLocation(programId, "texCoord");
	glEnableVertexAttribArray(textIndex);
	glVertexAttribPointer(textIndex,2,GL_FLOAT, GL_FALSE,0,0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexToreBuffer);
	glBindVertexArray(0);
}


inline glm::vec3 torusPoint(double theta, double phi, double R, double r) {
	float x, y,z;

	x = (R+r*cos(theta))*cos(phi);
	y = (R+r*cos(theta))*sin(phi);
	z = r*sin(theta);

	return glm::vec3(x,y,z); 
}


void makeATexturedTorus(Mesh *mesh, double R, double r, int nbBins) {
	int i=0,j=0;
	for (double theta=0; theta <= 2*M_PI; theta+=2*M_PI/nbBins){
		for (double phi=0; phi < 2*M_PI; phi+=2*M_PI/nbBins){
			int index = (i+1)%nbBins;
			int indexj = (j+1)%nbBins;

			Vertex tmp;
			tmp.addPosition(torusPoint(theta,phi,R,r));
			tmp.addColor(1,0,0,1);
			tmp.addUv(glm::vec2(0,0), glm::vec2(0,1), glm::vec2(1,1));
			tmp.addUv(glm::vec2(0,0), glm::vec2(1,1), glm::vec2(1,0));

			mesh->addIbos(i*nbBins+j, i*nbBins+indexj, index*nbBins+j);
			mesh->addIbos(index*nbBins+j, i*nbBins+indexj, index*nbBins+indexj);
			mesh->addVertex(tmp);

			longueurIndex+=6;
			j++;
		}
		j=0;
		i++;
	}
}

void renderFrame(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glUseProgram(programId);

	cam->update();

	GLuint locTime = glGetUniformLocation(programId,"uTime");
	glUniform1f(locTime,uTime);
	GLuint locView = glGetUniformLocation(programId,"view");
	glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(cam->getView()));
	GLint projLoc = glGetUniformLocation(programId, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(cam->getProjection()));

	glm::vec3 lightdirn = getLightDir();
	glm::vec3 lightcolor(0.4,0.6,0.4);
	GLint lightDirn = glGetUniformLocation(programId, "lightdirn");
	glUniform3fv(lightDirn,sizeof(lightdirn),(float*)&lightdirn);
	GLint lightColor = glGetUniformLocation(programId, "lightcolor");
	glUniform3fv(lightColor,sizeof(lightcolor),(float *)&lightcolor);
	glm::vec3 diffuse(0.9, 0.9, 0.9);
	GLint diffuseid = glGetUniformLocation(programId, "diffuse");
	glUniform3fv(diffuseid,sizeof(diffuse),(float *)&diffuse);


	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, longueurIndex, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);

	GLFWwindow* window = glfwGetCurrentContext();
	glfwSwapBuffers(window);
	glfwPollEvents();
}

glm::vec3 getLightDir() {
	// glm::mat4 rotL=glm::rotate(glm::mat4(), -cam->getCamX(), glm::vec3(1,0,0));
	// rotL=glm::rotate(rotL, -cam->getCamZ(), glm::vec3(0,0,1));
	glm::mat4 rotL;
	glm::vec3 lightdirn=glm::normalize(glm::mat3(rotL)*glm::vec3(0.4,0.6,0.4));
	return lightdirn;
}

void init(){
	initGLFW();
	initGLEW();
	make_resources();
}

void init_shaders(string* tempv, string* tempf, GLint* lengthv, GLint* lengthf, GLuint* shaderID){
	GLchar *vSource = (GLchar*)tempv->c_str();
	GLchar *fSource = (GLchar*)tempf->c_str();

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, (const GLchar**)&vSource, lengthv);
	glCompileShader(vShader);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);   
	glShaderSource(fShader, 1, (const GLchar**)&fSource, lengthf);
	glCompileShader(fShader);

	*shaderID = glCreateProgram();
	glAttachShader(*shaderID, vShader);
	glAttachShader(*shaderID, fShader);
	glLinkProgram(*shaderID);
}

void initGLFW(){
	if (!glfwInit()) {
		exit(1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WINDOW_WITH, WINDOW_HEIGHT, "Minimal OpenGL application with GLFW", NULL, NULL);
	if (!window) {
		cerr << "Could not open a window" << endl;
		exit(1);
	}
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwMakeContextCurrent(window);
}

void initGLEW() {
	glewExperimental = GL_TRUE;
	GLenum GlewInitResult = glewInit();
	if (GlewInitResult != GLEW_OK) {
		cerr << "ERROR: " << glewGetErrorString(GlewInitResult) << endl;
		exit(1);
	}
}

void make_shaders(string* tempv, string* tempf, GLint* lengthv, GLint* lengthf){
	*tempv = file_contents("../data/minimal.v.glsl", lengthv);
	*tempf = file_contents("../data/minimal.f.glsl", lengthf);
}

