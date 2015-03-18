#version 150

uniform sampler2D colormap;
uniform sampler2D normalmap; 
uniform int exercise; //0: ambient, 1: lambert, 2: gouraud, 3: phong, 4: phong + texture, 5: bump mapping
uniform float time;
// Assume light is directional
uniform vec3 lightdirn; 
uniform vec3 lightcolor; 
// material properties
uniform vec3 ambient; 
uniform vec3 diffuse; 
uniform vec3 specular; 
uniform float shininess; 
uniform vec3 spotpos;
uniform vec3 spotlookat;
uniform vec3 spotcolor;
uniform float spotangle;
in vec4 position;
in vec3 normal; 
in vec3 tangent; 
in vec3 bitangent;
in vec3 color; 
in vec2 uv;
out vec4 fragColor; 


vec3 ComputeLightLambert(const in vec3 lightdirn, const in vec3 lightcolor, const in vec3 normal, const in vec3 mydiffuse)/*{{{*/
{
    /*!todo exercise 1: Implement the diffuse (Lambertian) illumination model*/
    vec3 lambert = vec3(1);  
    return lambert;
}/*}}}*/


vec3 ComputeLightSpecular (const in vec3 lightdirn, const in vec3 lightcolor, const in vec3 normal, const in vec3 eyedirn, const in vec3 myspecular, const in float myshininess) /*{{{*/
{
    /*!todo exercise 3: Implement the specular (Blinn-Phong) illumination model*/
    vec3 phong = vec3(1); 
    return phong;
}/*}}}*/

void main()
{
    // chose interpolated or mapped normal depending on exercise
    vec3 fragNormal = normal;
    if(exercise>=5)
    {
        /*{{{*//*!todo exercise 5: Compute the normal for bump mapping
         * 1) read in the normalmap the value of the normal expressed in the tangent space
         * 2) express it in the eye coordinate frame
         * Set the new normal in the 'fragNormal' variable
         */
        /*}}}*/
        fragNormal = vec3(1);
    }
    fragNormal = normalize(fragNormal); 

    vec3 lambert = ComputeLightLambert(lightdirn, lightcolor, fragNormal, diffuse);

    /*!todo exercise 3: Compute the eye direction for the Phong model*//*{{{*/
    vec3 eyedirn = vec3(1);
    /*}}}*/
    float myshininess=shininess*(.8+ sin(time) * 0.5f);
    if(exercise>=5)
        myshininess=80;
    vec3 phong= ComputeLightSpecular(lightdirn, lightcolor, fragNormal, eyedirn, specular, myshininess);
    
    if(exercise==0)
        fragColor= vec4(ambient*color,1);
    else if(exercise==1)
        fragColor= vec4(ambient*color+lambert,1);
    else if(exercise==2)
        fragColor= vec4(color,1);
    else if(exercise==3)
        fragColor= vec4(ambient*color+lambert+phong,1);
    else if(exercise==4 || exercise>=5)
        fragColor= vec4(ambient*texture(colormap,
              uv).rgb+lambert*texture(colormap, uv).rgb+phong,1);
    if(exercise>=6)
    {
       //!fixme (this should be removed in the student version)
        vec3 spotdirn=normalize(spotpos - spotlookat);
        vec3 dirn=normalize(spotpos - position.xyz/position.w);
        if(dot(spotdirn, dirn)>cos(spotangle))
        {
            lambert = ComputeLightLambert(dirn, spotcolor, normal, diffuse);
            phong= ComputeLightSpecular(dirn, spotcolor, fragNormal, eyedirn, specular, shininess); 
            fragColor+=vec4(lambert*texture(colormap, uv).rgb+phong,1);
        }
    }
}
