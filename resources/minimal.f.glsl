#version 150

in vec4 vColor;
in vec2 outVertexUv;

out vec4 out_color;

uniform sampler2D colormap;
uniform float time;
uniform vec3 lightdirn;
uniform vec3 lightcolor;
uniform vec3 diffuse;

vec3 ComputeLightLambert(const in vec3 lightdirn, const in vec3 lightcolor, const in vec3 normal, const in vec3 mydiffuse) {
    return lightcolor*mydiffuse*max(0,dot(lightdirn,normal));
}

void main() {
//	vec3 lambert = ComputeLightLambert(lightdirn,lightcolor,glm::vec3(1,1,1),diffuse);
	out_color= texture(colormap,outVertexUv)*vColor;
}
