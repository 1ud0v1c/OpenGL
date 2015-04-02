#version 130
in vec3 position;
in vec3 normal;
in vec4 color;
in vec2 vertexUv;

out vec4 vColor;
out vec3 fNormal;
out vec2 outVertexUv;

uniform float time;
uniform mat4 view;
uniform mat4 proj;

void main() {
	gl_Position=proj*view*vec4(position, 1.0);
	vColor = color;
	outVertexUv = vertexUv;
}
