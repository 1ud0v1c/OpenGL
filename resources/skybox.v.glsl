#version 330 

layout (location = 0) in vec3 position;
out vec3 TexCoords;

uniform mat4 proj;
uniform mat4 view;

void main() {
	mat4 v = mat4(mat3(view));
	mat4 rotation = mat4(1,0,0,0, 0,-1,0,0, 0,0,-1,0, 0,0,0,1);
	gl_Position = proj * v * rotation * vec4(position, 1.0);
	TexCoords = position;
}  

