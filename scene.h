#ifndef SCENE_H
#define SCENE_H
#include "camera.h"
#include "controls.h"
#include "gameObject.h"

class Scene {
   public:
      Scene();
      ~Scene();
      void addObject(GameObject *object);
      void draw();
      void makeObject();
      void setType(GLuint type);
      void init(std::vector<GLuint> programms);
      void update(float time,GLFWwindow *window);
Camera* getCamera();
   private:
      std::vector<GameObject*> objects;
      Camera camera;
      std::vector<GLuint> transID;
      std::vector<GLuint> viewID;
      std::vector<GLuint> projID;
      std::vector<GLuint> timeID;
      std::vector<GLuint> programms;
      GLuint programm;
};
#endif
