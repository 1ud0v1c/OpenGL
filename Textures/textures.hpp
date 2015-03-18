void init(void);
void shutDown(int return_code);
void mainLoop(void);
void resize(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers);

int make_resources(void);
void draw();
void makeACubeMappedCube(ensi::gl::Mesh& cube, bool correct);
