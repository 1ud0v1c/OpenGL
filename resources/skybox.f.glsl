#version 330 

in vec3 TexCoords;
out vec4 color;

uniform samplerCube skybox;

void main() {    
	color = vec4(0.2,0.5,0.8,1); //texture(skybox, TexCoords);
}

