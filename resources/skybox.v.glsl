#version 330 

layout (location = 0) in vec3 position;
uniform vec3 offset;
out vec3 TexCoords;

uniform mat4 proj;
uniform mat4 view;

void main() {
	gl_Position = proj * view * vec4(position + offset, 1.0);
	TexCoords = position;
}  
