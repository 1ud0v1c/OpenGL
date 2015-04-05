#version 330

in vec4 vColor;
in vec3 fNormal;
in vec2 outVertexUv;

out vec4 out_color;

uniform sampler2D colormap;
uniform float time;
uniform vec3 lightdir;
uniform vec3 lightcolor;
uniform vec3 diffuse;
uniform vec3 lightpos;


vec3 ComputeLightLambert(const in vec3 lightdirn, const in vec3 lightcolor, const in vec3 normal, const in vec3 mydiffuse) {
    return lightcolor*mydiffuse*max(0,dot(lightdirn,normal));
}

void main() {
	vec3 lambert = ComputeLightLambert(vec3(cos(time),sin(time),0),lightcolor, fNormal,vec3(1,1,1));
	out_color=vec4(texture(colormap,outVertexUv).rgb*vec3(1.0f,0.9f,0.2f)+lambert,1.0);
}
