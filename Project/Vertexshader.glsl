#version 460
layout(location=0)in vec3  position;
layout(location = 1) in vec2 vertexColor;
layout(location = 2) in vec3 normals;
//layout(location=1)in vec2  colour;
 

out vec2 fragmentColor;
out vec3 lightdirection;

out vec3 normal;
 out vec3 fragposition;
 
 uniform mat4 modelmatrix;//matrix of the single model
//uniform mat4 viewmatrix;//matrix of the world
//uniform mat4 projectionmatrix;//matrix of the camera
uniform mat4 combinedmatrixes;
void main(){ 
gl_Position=combinedmatrixes* modelmatrix*vec4(position,1);
fragmentColor = vertexColor;
//uvs=colour;
normal=mat3(transpose(inverse(modelmatrix)))*normals;
 fragposition=vec3(modelmatrix*vec4(position,1));
}