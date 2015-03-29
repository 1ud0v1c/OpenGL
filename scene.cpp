#include "scene.h"
Scene::Scene() {
   numberTore = 0;
   numberSphere = 0;
}

void Scene::init(std::vector<GLuint> programms) {
   this->programms = programms;
   for( auto programm : programms) {
      viewID.push_back(glGetUniformLocation(programm, "view"));
      projID.push_back(glGetUniformLocation(programm, "projection"));
      timeID.push_back(glGetUniformLocation(programm, "uTime"));
   }
}

void Scene::update(float time,GLFWwindow *window) {
   camera.update();
   glm::mat4 proj = camera.getProjection();
   glm::mat4 view = camera.getView();
   glm::mat4 ModelMatrix = glm::mat4(1.0);
   for(int i=0;i<programms.size();i++) {
//      glUniformMatrix4fv(transID[i], 1, GL_FALSE, glm::value_ptr(ModelMatrix));
      glUniformMatrix4fv(viewID[i], 1, GL_FALSE, glm::value_ptr(view));
      glUniform1f(timeID[i],time);
      glUniformMatrix4fv(projID[i], 1, GL_FALSE, glm::value_ptr(proj));
   }
}

Scene::~Scene() {
}

void Scene::setType(GLuint type) {
   for(auto o : objects) {
      o->setType(type);
   }
}

void Scene::draw() {
   glUseProgram(programm);
   glUseProgram(0);
   for(auto o : objects) {
      glUseProgram(o->getProgramm());
      o->draw();
      glUseProgram(0);
   }
}

void Scene::makeObject() {
   int unit=0;
   for(auto o : objects) {
      o->makeObject();
      o->setUnit(unit);
      unit++;
   }
}

void Scene::addObject(GameObject *object) {
   if(object->getName() =="tore") numberTore++;
   if(object->getName() =="sphere") numberSphere++;
   objects.push_back(object);
}

Camera* Scene::getCamera(){
   return &camera;
}
