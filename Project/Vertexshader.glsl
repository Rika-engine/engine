#version 460
layout(location=0)in vec3  position;
layout(location=1)in vec3  color;
layout(location=2)in vec3  normals;
out vec3 colour;
//uniform mat4 modelmatrix;//matrix of the single model
//uniform mat4 viewmatrix;//matrix of the world
//uniform mat4 projectionmatrix;//matrix of the camera
uniform mat4 combinedmatrixes;
void main(){colour=color;
gl_Position=combinedmatrixes*vec4(position,1);
}