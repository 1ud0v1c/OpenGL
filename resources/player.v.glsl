#version 330

in vec3 position;
in vec3 normal;
in vec4 color;
in vec2 vertexUv;
layout (location = 6) in vec3 offset;

out vec4 vColor;
out vec3 fNormal;
out vec2 outVertexUv;

uniform float time;
uniform mat4 view;
uniform mat4 proj;
uniform vec3 moveOffset;

void main() {
	gl_Position=proj*view*vec4(position + offset + moveOffset, 1.0);
	vColor = color;
	outVertexUv = vertexUv;
	fNormal = normal;
}
