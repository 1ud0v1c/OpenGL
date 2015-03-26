#version 130
in vec3 position;
in vec3 color;
in vec2 texCoord;

out vec3 vColor;
out vec2 Texcoord;

uniform float uTime;
uniform mat4 view;
uniform mat4 projection;

void main() {
	mat3 mat = mat3(vec3(cos(uTime),-sin(uTime), 0), vec3(sin(uTime), cos(uTime), 0), vec3(0, 0, 1));
	gl_Position=projection*view*vec4(position*mat,1.0);
	vColor = color;
	Texcoord = texCoord;
}
