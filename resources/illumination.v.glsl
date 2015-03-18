#version 150
#extension GL_ARB_separate_shader_objects: require
// ins (inputs)
in vec3 vertexPosition;
in vec3 vertexNormal;
in vec3 vertexColor;
in vec2 vertexUV;
in vec3 vertexTangent;
// out (outputs)
out vec4 position;
out vec3 normal;
out vec3 tangent;
out vec3 bitangent;
out vec2 uv;
out vec3 color; 

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;
uniform int exercise;
uniform float time;
// Assume light is directional
uniform vec3 lightdirn; 
uniform vec3 lightcolor; 
// material properties
uniform vec3 ambient; 
uniform vec3 diffuse; 
uniform vec3 specular; 
uniform float shininess; 

vec3 ComputeLightLambert(const in vec3 lightdirn, const in vec3 lightcolor, const in vec3 normal, const in vec3 mydiffuse)/*{{{*/
{
    /*!todo exercise 1: Implement the diffuse (Lambertian) illumination model*/
    vec3 lambert = vec3(1);  
    return lambert;
}/*}}}*/


vec3 ComputeLightSpecular (const in vec3 lightdirn, const in vec3 lightcolor, const in vec3 normal, const in vec3 eyedirn, const in vec3 myspecular, const in float myshininess) /*{{{*/
{
    /*!todo exercise 3: Implement the specular (Phong) illumination model*/
    vec3 phong = vec3(1); 
    return phong;
}/*}}}*/

void main()
{
    vec4 positionH=vec4(vertexPosition,1);
    gl_Position =  projectionMatrix * modelViewMatrix *  positionH;
    position=modelViewMatrix * positionH;
    normal=normalMatrix * vertexNormal;
    normal=normalize(normal);
    tangent=mat3(modelViewMatrix) * vertexTangent;
    tangent=normalize(tangent);
    bitangent=cross(normal, tangent);
    color=vertexColor;
    uv=vertexUV; 
    if(exercise==2)
    {
        const vec3 eyepos = vec3(0,0,0); 
        vec3 fragNormal = normal;
        fragNormal=normalize(fragNormal);
        /*!todo exercise 2: Compute the eye direction for the Phong model*//*{{{*/
        vec3 eyedirn = vec3(1);
        /*}}}*/
        vec3 lambert = ComputeLightLambert(lightdirn, lightcolor, fragNormal, diffuse);
        float myshininess=shininess*(.8+ sin(time) * 0.5f);
        vec3 phong= ComputeLightSpecular(lightdirn, lightcolor, fragNormal, eyedirn, specular, myshininess);
        color= ambient*color+lambert+phong;
    }
}
