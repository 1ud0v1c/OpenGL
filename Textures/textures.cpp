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
#include "textures.hpp"/*}}}*/


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
   unsigned int nbEx=5;
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
   controls.window=glfwCreateWindow(window_width, window_height, "Texture mapping", NULL, NULL);
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
   // Create the scene/*{{{*/
   glm::mat4 mw;
   /* Dice material {{{*/
   ensi::gl::GLSLMaterial mat;
   // NB: tga files con be obtained with the imagemagick conversion tool as follows
   //     convert checkerboard.jpg -type TrueColor ../checkerboard.tga
   mat.uniformSamplers["colormap"]=loadTGATexture("dice.tga");
   mat.uniforms["diffuse"]=glm::vec3(1,0,0);
   ensi::gl::Program prog("texture.v.glsl", "texture.f.glsl");
   mat.program=prog;
   scene.materials["dice"]=mat;
   /*}}}*/
   /* Checkerboard material {{{*/
   ensi::gl::GLSLMaterial cbMat;
   cbMat.uniformSamplers["colormap"]=loadTGATexture("checkerboard.tga");
   cbMat.uniforms["diffuse"]=glm::vec3(1,1,0);
   cbMat.program=prog;
   scene.materials["checkerboard"]=cbMat;
   /*}}}*/
   /* Simple material {{{*/
   ensi::gl::GLSLMaterial simpleMat;
   prog=ensi::gl::Program("simple.v.glsl", "simple.f.glsl");
   simpleMat.program=prog;
   scene.materials["simple"]=simpleMat;
   /*}}}*/
   // bad cube 1/*{{{*/
   ensi::gl::Mesh badcube;
   makeACubeMappedCube(badcube,false);
   mw=controls.modelWorldMatrix.top();
   mw=glm::scale(mw, glm::vec3(2,2,2));
   mw=glm::translate(mw, glm::vec3(-1,0.5,0.5));
   scene.addObject("badcube", badcube, mw);/*}}}*/
   // bad cube 2/*{{{*/
   mw=controls.modelWorldMatrix.top();
   mw=glm::scale(mw, glm::vec3(2,2,2));
   mw=glm::translate(mw, glm::vec3(1,0.5,0.5));
   scene.addInstance("badcube",  mw, "badcube 2");/*}}}*/
   // cube/*{{{*/
   ensi::gl::Mesh cube;
   mw=controls.modelWorldMatrix.top();
   mw=glm::scale(mw, glm::vec3(2,2,2));
   mw=glm::translate(mw, glm::vec3(1,0.5,0.5));
   makeACubeMappedCube(cube,true);
   scene.addObject("cube", cube, mw);/*}}}*/
   // plane/*{{{*/
   ensi::gl::Mesh plane=badcube;
   mw=controls.modelWorldMatrix.top();
   mw=glm::scale(mw, glm::vec3(20,20,0.1));
   mw=glm::translate(mw, glm::vec3(0,0.5,0));
   for(ensi::gl::Vertex& v: plane.m_verts){
      v.uv=v.position.xy();
      v.uv*=20;
   }
   scene.addObject("plane", plane, mw);/*}}}*/
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
   if(controls.exercise>=1)/*{{{*/
   {
      // Nothing to be done here
      scene.drawObject("badcube","dice");
      if(controls.exercise>=2)
	 scene.drawObject("cube","dice");
      else
	 scene.drawObject("badcube 2","dice");
   }
   else
   {
      scene.drawObject("badcube","simple");
      scene.drawObject("cube","simple");
   }/*}}}*/
   GLuint checkerboardTextureLoc=scene.materials["checkerboard"].uniformSamplers["colormap"];
   if(controls.exercise>=3) {
      /*!todo exercise 3: generate mipmaps and activate them for the min filter*/

      glBindTexture(GL_TEXTURE_2D, checkerboardTextureLoc);
      glGenerateMipmap(GL_TEXTURE_2D);
   	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

      if(controls.exercise>=4) {
		GLfloat max = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max);
   	  	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max);
      } else {

      }

   }
   else
   {
      glBindTexture(GL_TEXTURE_2D, checkerboardTextureLoc);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
   }/*}}}*/
   if(controls.exercise>=1)
      scene.drawObject("plane","checkerboard");
   else
      scene.drawObject("plane","simple" );
   glDisable(GL_CULL_FACE);
   glDisable(GL_DEPTH_TEST);
}
/*}}}*/

void makeACubeMappedCube(ensi::gl::Mesh& cube, bool correct)/*{{{*/
{
   using ensi::gl::Vertex;
   cube.m_verts.clear();
   cube.m_tris.clear();
   std::vector<glm::vec3> ps, ns, ts, bs;
   //make the front face (y=0)/*{{{*/
   glm::vec3 p0(0,0,0);
   glm::vec3 p1(1,0,0);
   glm::vec3 p2(1,0,1);
   glm::vec3 p3(0,0,1);
   glm::vec3 n0(0,-1,0);
   glm::vec3 n1(0,-1,0);
   glm::vec3 n2(0,-1,0);
   glm::vec3 n3(0,-1,0);  
   glm::vec3 pp0(0,1,0);
   glm::vec3 pp1(0,1,1);
   glm::vec3 pp2(1,1,1);
   glm::vec3 pp3(1,1,0);
   glm::vec3 nn0(0,1,0);
   glm::vec3 nn1(0,1,0);
   glm::vec3 nn2(0,1,0);
   glm::vec3 nn3(0,1,0);  /*}}}*/
   // for each axis create two faces
   for (int i = 0; i < 3; ++i)/*{{{*/
   {
      int ix=i, iy=(i+1)%3, iz=(i+2)%3;
      // first face
      ps.push_back(glm::vec3(p0[ix]-0.5,p0[iy]-0.5,p0[iz]-0.5));
      ns.push_back(glm::vec3(n0[ix],n0[iy],n0[iz]));

      ps.push_back(glm::vec3(p1[ix]-0.5,p1[iy]-0.5,p1[iz]-0.5));
      ns.push_back(glm::vec3(n1[ix],n1[iy],n1[iz]));

      ps.push_back(glm::vec3(p2[ix]-0.5,p2[iy]-0.5,p2[iz]-0.5));
      ns.push_back(glm::vec3(n2[ix],n2[iy],n2[iz]));


      ps.push_back(glm::vec3(p0[ix]-0.5,p0[iy]-0.5,p0[iz]-0.5));
      ns.push_back(glm::vec3(n0[ix],n0[iy],n0[iz]));

      ps.push_back(glm::vec3(p2[ix]-0.5,p2[iy]-0.5,p2[iz]-0.5));
      ns.push_back(glm::vec3(n2[ix],n2[iy],n2[iz]));

      ps.push_back(glm::vec3(p3[ix]-0.5,p3[iy]-0.5,p3[iz]-0.5));
      ns.push_back(glm::vec3(n3[ix],n3[iy],n3[iz]));


      // second face
      ps.push_back(glm::vec3(pp0[ix]-0.5,pp0[iy]-0.5,pp0[iz]-0.5));
      ns.push_back(glm::vec3(nn0[ix],nn0[iy],nn0[iz]));

      ps.push_back(glm::vec3(pp1[ix]-0.5,pp1[iy]-0.5,pp1[iz]-0.5));
      ns.push_back(glm::vec3(nn1[ix],nn1[iy],nn1[iz]));

      ps.push_back(glm::vec3(pp2[ix]-0.5,pp2[iy]-0.5,pp2[iz]-0.5));
      ns.push_back(glm::vec3(nn2[ix],nn2[iy],nn2[iz]));


      ps.push_back(glm::vec3(pp0[ix]-0.5,pp0[iy]-0.5,pp0[iz]-0.5));
      ns.push_back(glm::vec3(nn0[ix],nn0[iy],nn0[iz]));

      ps.push_back(glm::vec3(pp2[ix]-0.5,pp2[iy]-0.5,pp2[iz]-0.5));
      ns.push_back(glm::vec3(nn2[ix],nn2[iy],nn2[iz]));

      ps.push_back(glm::vec3(pp3[ix]-0.5,pp3[iy]-0.5,pp3[iz]-0.5));
      ns.push_back(glm::vec3(nn3[ix],nn3[iy],nn3[iz]));

   }/*}}}*/
   std::vector<glm::vec2> uvs={
      glm::vec2(0,0), glm::vec2(0,1),  glm::vec2(1,1),
      glm::vec2(0,0),  glm::vec2(1,1), glm::vec2(1,0),
      glm::vec2(0,0), glm::vec2(0,1),  glm::vec2(1,1),
      glm::vec2(0,0),  glm::vec2(1,1), glm::vec2(1,0),
      //
      glm::vec2(0,0), glm::vec2(0,1),  glm::vec2(1,1),
      glm::vec2(0,0),  glm::vec2(1,1), glm::vec2(1,0),
      glm::vec2(0,0), glm::vec2(0,1),  glm::vec2(1,1),
      glm::vec2(0,0),  glm::vec2(1,1), glm::vec2(1,0),
      //
      glm::vec2(0,0), glm::vec2(0,1),  glm::vec2(1,1),
      glm::vec2(0,0),  glm::vec2(1,1), glm::vec2(1,0),
      glm::vec2(0,0), glm::vec2(0,1),  glm::vec2(1,1),
      glm::vec2(0,0),  glm::vec2(1,1), glm::vec2(1,0),
   };
   /*!todo exercise 2: Create the correct uv values to have each number mapped on one of the faces *//*{{{*/
   if(correct)
   {
      uvs={ 
		// Face 1
	 	glm::vec2(0.25,0.33), glm::vec2(0.5,0.33), glm::vec2(0.5,0.66),
		glm::vec2(0.25,0.33), glm::vec2(0.5,0.66), glm::vec2(0.25,0.66), 
		// Face 6
	 	glm::vec2(0.75,0.33), glm::vec2(1,0.33),  glm::vec2(1,0.66),
	 	glm::vec2(0.75,0.33),  glm::vec2(1,0.66), glm::vec2(0.75,0.66),
	 	// Face 5
	 	glm::vec2(0,0.33), glm::vec2(0.25,0.33),  glm::vec2(0.25,0.66),
	 	glm::vec2(0,0.33),  glm::vec2(0.25,0.66), glm::vec2(0,0.66),
		// Face 2
	 	glm::vec2(0.5,0.33), glm::vec2(0.75,0.33),  glm::vec2(0.75,0.66),
	 	glm::vec2(0.5,0.33),  glm::vec2(0.75,0.66), glm::vec2(0.5,0.66),
	 	// Face 4 
	 	glm::vec2(0.25,0), glm::vec2(0.5,0),  glm::vec2(0.5,0.33),
	 	glm::vec2(0.25,0),  glm::vec2(0.5,0.33), glm::vec2(0.25,0.33),
		// Face 3
	 	glm::vec2(0.25,0.66), glm::vec2(0.5,0.66),  glm::vec2(0.5,1),
	 	glm::vec2(0.25,0.66),  glm::vec2(0.5,1), glm::vec2(0.25,1),
      };                         
   }
   /*}}}*/
   computeTangentBasis(ps, uvs, ns, ts, bs);
   std::vector<glm::vec3> ops, ons, ots, obs;
   std::vector<glm::vec2> ouvs;
   indexVBO_TBN(ps, uvs, ns, ts, bs, cube.m_tris, ops, ouvs, ons, ots, obs);
   const glm::vec4 colors[]={glm::vec4(1,0,0,1), glm::vec4(1,1,0,1), glm::vec4(0,1,0,1), glm::vec4(0,1,1,1), glm::vec4(0,0,1,1), glm::vec4(1,0,1,1)};
   for (unsigned int i = 0; i < ops.size(); ++i)
   {
      Vertex v(ops[i], ons[i], ouvs[i], colors[i/4], ots[i]);
      cube.m_verts.push_back(v);
   }
   cube.computeBSphere();
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
