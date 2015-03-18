#version 150

in vec4 color; 
in vec2 uv;
out vec4 fragColor ; 

uniform sampler2D colormap;
uniform vec3 diffuse;

void main()
{
    fragColor=texture(colormap, uv);
    //*vec4(diffuse,1);
}
