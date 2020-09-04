#version 460


struct Light {
	float power;
 vec3 direction;
 vec3 color;
};







in vec2 fragmentColor;
 in vec3 normal;
  in vec3 fragposition;
out vec4 color;

layout(binding=0)uniform sampler2D textureid; 
 
layout(binding=1)uniform sampler2D textureid2; 
 uniform vec3 lightpos;
uniform vec3 viewpos ;
vec3 ambient;

//uniform sampler2D normaltexture;
//uniform sampler2D bumptexture;
void main(){//color=vec3( 1,1,1);
 // color = fragmentColor;

 ambient=vec3(0.5)*vec3(texture(textureid ,vec2(fragmentColor.x,1- fragmentColor.y)));;


 Light light;
 light.color=vec3(1,1,1);
 light.direction=(normalize(vec3(lightpos.x,lightpos.y, lightpos.z)-vec3(fragposition.x,fragposition.y,fragposition.z)));
 light.power=2.5;

 color=vec4(normal.x,normal.y,normal.z,1);

 float diffuse=clamp(dot(normalize((normal)),light.direction),0,1); 
vec3 diff=light.color*diffuse*light.power  ;

; 


color=vec4(1);
color=texture(textureid,vec2(fragmentColor.x,1-fragmentColor.y))  ;
vec3 viewdir=normalize(viewpos-fragposition);
 
vec3 reflectdir = reflect(-light.direction, normal);  
float spec=pow(max(dot(viewdir,reflectdir),0.6),11);
vec3 specc=spec*light.color *vec3(texture(textureid ,vec2(fragmentColor.x,1-fragmentColor.y)));color=color*vec4(ambient+diff  ,1);
 
}