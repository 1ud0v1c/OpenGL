#version 330
in vec4 position;
layout(location = 1) in vec4 xyzs; // Position of the center of the particule and size of the square
layout(location = 2) in vec4 color; // Position of the center of the particule and size of the square
layout(location = 3) in vec3 dir;
layout(location = 4) in float speed;
out vec4 vColor;
uniform mat4 trans;
uniform mat4 view;
uniform mat4 proj;
uniform float time;
uniform float time2;
uniform vec3 moveOffset;

void main()
{
	float particleSize = xyzs.w;
	mat4 scale = mat4(vec4(particleSize,0,0,0),
			vec4(0,particleSize,0,0),
			vec4(0,0,particleSize,0),
			vec4(0,0,0,1));
	vec4 v=scale*vec4(position.xyz +moveOffset +xyzs.xyz+dir*speed*time,1.0);
	gl_Position = proj*view*trans* v;
	vColor = color;
}
