/* Include headers*//*{{{*/
#include <stdlib.h>
#include <iostream>
#include <stack>
#include <vector>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
// matrix and vectors
// to declare before including glm.hpp, to use the swizzle operators
#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
//loading stuffs
#include "utils/utils.h"
#include "utils/shaders.h"
#include "utils/textures.h"
#include "utils/objloader.h"
#include "../include/lightGlAPI.hpp"
#include "shading.hpp"/*}}}*/


//-------------------- MAIN /*{{{*/
int main(void)/*{{{*/
{
    init();
    mainLoop();
    shutDown(0);
}/*}}}*/

void mainLoop(void)/*{{{*/
{
    ensi::gl::Scene& scene = ensi::gl::Scene::getInstance();
    ensi::gl::Controls& controls=scene.controls;
    // this just loops as long as the program runs
    while(!glfwWindowShouldClose(controls.window))
    {
        /* Calculate time elapsed, and the amount by which stuff rotates*//*{{{*/
        double current_time = glfwGetTime();
        controls.setTime(current_time);
        controls.updateView();
        /*}}}*/

        /* Additional key handling (when repeat key is needed)*//*{{{*/
        // escape to quit, arrow keys to rotate view
        if (glfwGetKey(controls.window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwGetKey(controls.window, 'Q') == GLFW_PRESS)
            break;
        controls.continuousKeyCallback();
        /*}}}*/

        /* Send all the drawing commands and swap the buffers*//*{{{*/
        draw();
        // swap back and front buffers
        glfwSwapBuffers(controls.window);
        glfwPollEvents();
        controls.resetView();
        /*}}}*/
    }
}/*}}}*/
/*}}}*/


//-------------------- Inits/*{{{*/
void init(void)/*{{{*/
{ 
    //-------------------- Globals/*{{{*/
    unsigned int nbEx=7;
    ensi::gl::Scene& scene = ensi::gl::Scene::getInstance();
    ensi::gl::Renderer* renderer=new ensi::gl::GLRenderer();
    scene.setRenderer(renderer);
    ensi::gl::Controls& controls=scene.controls;
    controls.nbExercises=nbEx;
    /*}}}*/
    /* GLFW initialization *//*{{{*/
    const int window_width = 1024, window_height = 800;
    if (!glfwInit())
        shutDown(1);
    // Create OpenGL 3.x Core Profile Context                                                   
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
#endif
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 800 x 600, default bit color, 32 bit depth, no alpha or stencil buffers, windowed
    controls.window=glfwCreateWindow(window_width, window_height, "Shading", NULL, NULL);
    if (!controls.window)
    {
        std::cerr<<"Could not open a window"<<std::endl;
        shutDown(1);
    }
    glfwMakeContextCurrent(controls.window);
    /*}}}*/
    
    /* GLEW Initialization *//*{{{*/
    // Do not forget to use glewExperimental so that glewInit works with core
    // profile: http://www.opengl.org/wiki/OpenGL_Loading_Library#GLEW
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();
    std::cout<<"Here, we should expect to get a GL_INVALID_ENUM (that's a known bug), and indeed:"<<std::endl;
    checkGLerror();
    if (GlewInitResult != GLEW_OK) {
        std::cerr<<"ERROR: "<< glewGetErrorString(GlewInitResult)<<std::endl;
        shutDown(1);
    }/*}}}*/
    
    /* GLFW callbak definitions *//*{{{*/
    glfwSetFramebufferSizeCallback(controls.window, &resize);
    glfwSetKeyCallback(controls.window, keyCallback);
    glfwSetMouseButtonCallback(controls.window, mouseButtonCallback);
    /*}}}*/
    
    /* Creating the controls*//*{{{*/
    int width;
    int height;
    glfwGetFramebufferSize(controls.window, &width, &height);
    resize(controls.window, width, height);
    /*}}}*/

    /* Creating OpenGL resources *//*{{{*/
    make_resources();
    std::cout<<"Seems we made it "<<std::endl;
    std::cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<std::endl;
    std::cout<<"GLSL version: "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;/*}}}*/
}/*}}}*/

int make_resources(void)/*{{{*/
{
    ensi::gl::Scene& scene = ensi::gl::Scene::getInstance();
    ensi::gl::Controls& controls=scene.controls;
    //!Important: Set the attribute locations:
    // Now create a program
    ensi::gl::Program prog("illumination.v.glsl", "illumination.f.glsl", "illumination");
    // Create the scene/*{{{*/
    glm::mat4 mw;
    /* Checkerboard material {{{*/
    ensi::gl::GLSLMaterial cbMat;
    cbMat.uniformSamplers["colormap"]=loadTGATexture("checkerboard.tga");
    cbMat.uniformSamplers["normalmap"]=loadTGATexture("checkerboard_normalmap.tga");
    cbMat.uniforms["diffuse"]=glm::vec3(1,1,1);
    cbMat.uniforms["specular"]=glm::vec3(0.7,0.7,0.7);
    cbMat.uniforms["shininess"]=500.;
    cbMat.program=prog;
    scene.materials["checkerboard"]=cbMat;
    /*}}}*/
    /* Stone material {{{*/
    ensi::gl::GLSLMaterial stoneMat;
    stoneMat.uniformSamplers["colormap"]=loadTGATexture("brick_colormap.tga");    
    stoneMat.uniformSamplers["normalmap"]=loadTGATexture("brick_normalmap.tga");
    stoneMat.uniforms["diffuse"]=glm::vec3(1,1,1);
    stoneMat.uniforms["specular"]=glm::vec3(0.7,0.7,0.7);
    stoneMat.uniforms["shininess"]=500.;
    stoneMat.program=prog;
    scene.materials["stone"]=stoneMat;
    /*}}}*/
    /* Dice material {{{*/
    ensi::gl::GLSLMaterial diceMat;
    diceMat.uniformSamplers["colormap"]=loadTGATexture("dice_colormap.tga");
    diceMat.uniformSamplers["normalmap"]=loadTGATexture("dice_normalmap.tga");
    diceMat.uniforms["diffuse"]=glm::vec3(1,1,1);
    diceMat.uniforms["specular"]=glm::vec3(0.7,0.7,0.7);
    diceMat.uniforms["shininess"]=500.;
    diceMat.program=prog;
    scene.materials["dice"]=diceMat;
    /*}}}*/
    /* DiceHR material {{{*/
    diceMat.uniformSamplers["normalmap"]=loadTGATexture("blank_normalmap.tga");
    scene.materials["diceHR"]=diceMat;
    /*}}}*/
    /* floor {{{ */
    ensi::gl::Mesh floor;
    floor.makeMeCube(glm::vec4(1,1,1,1));
    for ( unsigned int i = 0; i < floor.m_verts.size(); ++i)
    {
        ensi::gl::Vertex& v=floor.m_verts[i];
        v.uv=v.position.xy();
        v.uv*=5;
    }
    mw=glm::scale(mw, glm::vec3(40,40,0.2));
    scene.addObject("floor", floor, mw);
    /* }}} floor */
    /* suzanne {{{ */
    ensi::gl::Mesh suzanne;
    suzanne.loadObj( "suzanne.obj", glm::vec4(0,0,1,1));
    mw=glm::mat4();
    mw=glm::translate(mw, glm::vec3(-2,2,0.6));
    mw=glm::rotate(mw, glm::pi<float>()/4, glm::vec3(1,0,0));
    mw=glm::scale(mw, glm::vec3(2,2,2));
    scene.addObject("suzanne", suzanne, mw);
    /* }}} suzanne */
    /* teapot {{{ */
    ensi::gl::Mesh teapot;
    teapot.loadObj( "teapot.obj", glm::vec4(1,1,0,1));
    mw=glm::mat4();
    mw=glm::translate(mw, glm::vec3(2,-2,0.6));
    mw=glm::scale(mw, glm::vec3(2,2,2));
    scene.addObject("teapot", teapot, mw);
    /* }}} teapot */
    /* dice {{{ */
    ensi::gl::Mesh dice;
    dice.loadObj( "dice.obj", glm::vec4(1,0,0,1));
    mw=glm::mat4();
    mw=glm::translate(mw, glm::vec3(-2,-2,0.6));
    scene.addObject("dice", dice, mw);
    /* }}} dice */
    /* diceHR {{{ */
    ensi::gl::Mesh diceHR;
    dice.loadObj( "diceHR.obj", glm::vec4(1,0,0,1));
    mw=glm::mat4();
    mw=glm::translate(mw, glm::vec3(2,2,0.6));
    scene.addObject("diceHR", dice, mw);
    /* }}} diceHR */
    /*}}}*/
    return 1;
}/*}}}*/
/*}}}*/


void draw()/*{{{*/
{
    ensi::gl::Scene& scene = ensi::gl::Scene::getInstance();
    ensi::gl::Controls& controls=scene.controls;
    // clear the buffer
    glClear(GL_COLOR_BUFFER_BIT );
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);
    std::string matnames[4]={"checkerboard", "stone", "dice", "diceHR"};
    for( const std::string& matname : matnames)
    {
        /*!todo: Spot stuff for the bonus execise{{{*/
        /*}}}*/
    }
    scene.drawObject("floor","checkerboard");
    scene.drawObject("suzanne","stone");
    scene.drawObject("teapot","stone");
    scene.drawObject("dice","dice");
    scene.drawObject("diceHR","diceHR");
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
}
/*}}}*/


//-------------------- GLFW Callbacks/*{{{*/
void shutDown(int return_code)/*{{{*/
{
    glfwTerminate();
    exit(return_code);
}/*}}}*/

void resize(GLFWwindow* window, int width, int height)/*{{{*/
{        
    ensi::gl::Scene& scene = ensi::gl::Scene::getInstance();
    ensi::gl::Controls& controls=scene.controls;
    controls.resize(width, height);
}/*}}}*/

void keyCallback(GLFWwindow* window, int key, int scancode,  int action, int modifiers)/*{{{*/
{
    ensi::gl::Scene& scene = ensi::gl::Scene::getInstance();
    ensi::gl::Controls& controls=scene.controls;
    controls.keyCallback(key, action, modifiers);
}/*}}}*/

void mouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers)/*{{{*/
{
    ensi::gl::Scene& scene = ensi::gl::Scene::getInstance();
    ensi::gl::Controls& controls=scene.controls;
    controls.mouseButtonCallback(button, action);
}/*}}}*/
/*}}}*/
// vim: foldmethod=marker autoread:
