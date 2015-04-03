#include "box.h"

Box::Box(float x,float y,float z, float w, float h, float d) {
this->	x = x;
this->	y = y;
this->	z = z;
this->	w = w;
this->	h = h;
this->	d = d;


}

bool Box::AABB(Box *b) {

	if(glm::abs(x - b->x) < w + b->w)
	{
		//check the Y axis
		if(glm::abs(y - b->y) < h + b->h)
		{
			//check the Z axis
			if(glm::abs(z - b->z) < d + b->d)
			{
				return true;
			}
		}
	}

	return false;
}
