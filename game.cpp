#include "game.h"
#include "utils.h"
#include "gameSphere.h"
#include "player.h"

using namespace std;

Game::Game() {
}

void Game::init() {
	initGLFW();
	initGLEW();
	type = GL_TRIANGLES;
	programms["minimal"] = createShaders("minimal.v.glsl","minimal.f.glsl");
	programms["text2D"] = createShaders("text2D.v.glsl","text2D.f.glsl");
	programms["skybox"] = createShaders("skybox.v.glsl","skybox.f.glsl");
	programms["player"] = createShaders("player.v.glsl","player.f.glsl");

	make_resources();
}

void Game::initGLFW() {
	if (!glfwInit()) shutDown(1);
	// Create OpenGL 4.4 Core Profile and Forward Compatible Context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Create a window of given size
	window = glfwCreateWindow(width, 600,"Minimal OpenGL application with GLFW", NULL, NULL);
	if (!window) {
		std::cerr<<"Could not open a window"<<std::endl;
		shutDown(1);
	}
	// Make the context of the specified window current
	glfwMakeContextCurrent(window);
}

void Game::initGLEW() {
	glewExperimental = GL_TRUE;
	GLenum GlewInitResult = glewInit();
	if (GlewInitResult != GLEW_OK) {
		std::cerr<<"ERROR: "<< glewGetErrorString(GlewInitResult)<<std::endl;
		shutDown(1);
	}
}

void Game::make_resources() {
}

void Game::renderFrame() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	scene.draw();
	GLFWwindow *window = glfwGetCurrentContext();
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Game::run() {
	scene = Scene();
	scene.init(programms);
	scene.makeObject();
	Player* player = scene.getPlayer();
	float dt = 1/60.0f;
	float time = 0;
	float time2 = 0;
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	bool pressL=false;
	while(!(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)) {
		glUseProgram(programm);
		if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && pressL == false){
			if(type == GL_TRIANGLES) type = GL_LINES;
			else type = GL_TRIANGLES;
			scene.setType(type);
			pressL = true;
		}
		if(glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE) pressL = false;
		while(time<dt)
			time+=0.01;
		time=0;
		time2+=0.01;
		scene.update(time2,window,dt);
		player = scene.getPlayer();
		if(player->getLives() == 0){
			std::cout << "GAME OVER ! " << std::endl;
			player->modifyScore(time2);
			std::cout << "Score final : " << player->getScore();
			break;
		}
		glfwPollEvents();
		renderFrame();
	}
	shutDown(0);
}

void Game::shutDown(int i) {
	glfwTerminate();
}


GLuint Game::createShaders(const std::string & vertex, const std::string & fragment) {
	GLint length1;
	GLint length2;
	std::string vs;
	std::string fs;
	vs = file_contents(vertex, &length1);
	fs = file_contents(fragment, &length2);
	GLchar *vSource = (GLchar*)vs.c_str();
	GLchar *fSource = (GLchar*)fs.c_str();
	//---- GPU side (Load and compile)
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, (const GLchar**)&vSource, &length1);
	glCompileShader(vShader);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, (const GLchar**)&fSource, &length2);
	glCompileShader(fShader);
	//---- GPU side (Link)
	programm = glCreateProgram();
	glAttachShader(programm, vShader);
	glAttachShader(programm, fShader);
	glLinkProgram(programm);
	return programm;
}



Game::~Game(){
}
