#ifndef BOX_H
#define BOX_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
class Box {
	public:
		Box(float x,float y,float z, float w, float h, float d);
		bool AABB(Box *b);
		float x,y,z,w,h,d;

	private:



};

#endif
