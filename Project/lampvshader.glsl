#version 460
layout(location=0)in vec3  position;
layout(location = 1) in vec2 vertexColor;
layout(location = 2) in vec3 normals;
 
 

 
 uniform mat4 modelmatrix;//matrix of the single model
 
uniform mat4 combinedmatrixes;
void main(){ 
gl_Position=combinedmatrixes* modelmatrix*vec4(position,1);
 
 
 
}