#ifndef SCENE_H
#define SCENE_H
#include "camera.h"

class Scene {
   public:
      Scene();
      ~Scene();
     // void addObject(GameObject *object);
      void draw();
      void makeObject();
      void setType(GLuint type);
      void init(std::vector<GLuint> programms);
      void update(float time,GLFWwindow *window);
   private:
//      std::vector<GameObject*> objects;
      Camera camera;
      std::vector<GLuint> transID;
      std::vector<GLuint> viewID;
      std::vector<GLuint> projID;
      int numberTore;
      int numberSphere;
      std::vector<GLuint> timeID;
      std::vector<GLuint> programms;
      GLuint programm;
};
#endif
