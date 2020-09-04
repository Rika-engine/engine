#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include "ddsimporter.h"

#include  <glm.hpp>
#include <gtc/type_ptr.hpp>

#include <direct.h>


GLuint bindshader(const char* vname, const char* fname) {
	std::string s,s2;
	GLuint vertexshaderid= glCreateShader(GL_VERTEX_SHADER);;
	GLuint fragmentshaderid= glCreateShader(GL_FRAGMENT_SHADER);;
 
	std:: ifstream f;
	f.open(vname);
	if (f.is_open()) {

		while (getline(f, s)) {
			s2 = s2 + s+"\n";
		}
	}
	else { std::printf("Unable to open the shader file"); }
	f.close();
	const char* lines=s2.c_str();
	glShaderSource(vertexshaderid, 1, &lines, 0);

	glCompileShader(vertexshaderid);
	std::printf(s2.c_str());
	s2 = "";
	std::printf(s2.c_str());

	f.open(fname);
	if (f.is_open()) {

		while (getline(f, s)) {
			s2 = s2 + s + "\n";
		}
	}
	else { std::printf("Unable to open the shader file"); }
	f.close();
	lines = s2.c_str();
	glShaderSource(fragmentshaderid, 1, &lines, 0);

	glCompileShader(fragmentshaderid);
	int welldone,infolenght;
	glGetShaderiv(vertexshaderid, GL_COMPILE_STATUS, &welldone);
	if (!welldone) {
		std::printf("adsas");
		glGetShaderiv(vertexshaderid, GL_INFO_LOG_LENGTH, &infolenght);
		std::vector <char> c(infolenght + 1);
		
		glGetShaderInfoLog(vertexshaderid, infolenght, NULL, &c[0]);//&c[0]==.data(),same thing
		std::printf(&c[0]);
	}

	glGetShaderiv(fragmentshaderid, GL_COMPILE_STATUS, &welldone);
	if (!welldone) {
		std::printf("FRAGMENT SHADER");
		glGetShaderiv(fragmentshaderid, GL_INFO_LOG_LENGTH, &infolenght);
		std::vector <char> c(infolenght + 1);

		glGetShaderInfoLog(fragmentshaderid, infolenght, NULL, &c[0]);//&c[0]==.data(),same thing
		std::printf(&c[0]);
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexshaderid);
	glAttachShader(program, fragmentshaderid);
	glLinkProgram(program);
	return program;
}


string  getpath() {
	char C[256];
	_getcwd(C, sizeof(C));
	std::string path = C;
	path = path.substr(0, path.find("Project"));
	path.insert(path.find("\\", path.find("\\")), "\\");
	short a = path.find("\\");
	while (path.find("\\", a + 3) != -1) {
		a = path.find("\\", a + 3); std::printf("\n %s path\n", path.c_str());
		path.insert(path.find("\\", a), "\\");

		std::printf("\n %d XD ", a);;
	}

	std::printf("\n %s path\n", path.c_str());
	return path;
}
void loadtexture(const char* name,GLuint &textureid ) {
	string path = getpath()+"models\\"+name+"\\"+name+".dds";
 

	float anisot = 0;
 
	if(GL_EXT_texture_filter_anisotropic){
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisot);
	//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisot);
	}
	
	
	
	 
	


	glGenTextures(1, &textureid); std::printf("ttttt%d  ", textureid);
	 
	glUniform1i(0, textureid);
	glBindTexture(GL_TEXTURE_2D, textureid);
	glActiveTexture(0);

	std::printf("aaaaa %d  ", textureid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	 
	loaddds(path.c_str());


 

	GLuint  textureid2=0;
 
	glGenTextures(1, &textureid2); std::printf("ttttt%d  ", textureid2);
	glBindTexture(GL_TEXTURE_2D, textureid);
	glActiveTexture(0);
	glUniform1i(1, textureid2);
	std::printf("aaaaa %d  ", textureid2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
 



 
	 
	// loaddds(s.c_str());
	


 

 }


void cameramovmnt(GLuint &program,GLFWwindow *window,double width,double height,glm::vec3 &cam,glm::mat4 &viewmatrix) {

	static float xoffset = 0; static float yoffset = 0;
	
	float time = glfwGetTime();
	float deltatime = glfwGetTime(); -time;
	float verticalangle=0, horizontalangle=0;
	float fov;//field of view,zoom;
	static double pitch=0, yaw=0, roll=0;
	double xpos, ypos;

	float speed = 0.015, mousespeed = 0.033;

	


	glm::vec3 direction;
 //trygonometry
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, width / 2, height / 2);
	xoffset = xpos;
	
	yoffset = ypos;

	yaw = yaw + mousespeed * ((width / 2)- xpos)  ;
	pitch = pitch + mousespeed * ((height / 2) - ypos)  ;
	if (pitch < -89) {
		pitch =- 89;
	}


	if (yaw > 179) {
		yaw = 179;
	}

	if (pitch > 89) {
		pitch = 89;
	}

	if (yaw <- 179) {
		yaw = -179;
	}

	glm::vec3 destra = glm::vec3(
		sin(yaw - 3.14f / 2.0f),
		0,
		cos(pitch - 3.14f / 2.0f)
	);
 
		direction.x = cos(glm::radians(yaw))*cos(glm::radians(pitch)); //  
		direction.y = sin(glm::radians(pitch))  ; //  
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));;



	







	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cam = cam + speed * deltatime * direction;

	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cam = cam - speed * deltatime * direction;

	}
	glm::vec3 up = glm::vec3(0, 1, 0);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cam = cam + speed * deltatime * glm::normalize(glm::cross(up, direction));

	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cam = cam - speed *deltatime* glm::normalize(glm::cross(up, direction));//three finger rule

	}
 
	viewmatrix=glm::lookAt(cam, cam +  direction, up);
 
	
	glm::vec3 right = glm::vec3(
		sin(horizontalangle - 3.14f / 2.0f),
		0,
		cos(horizontalangle - 3.14f / 2.0f)
	);


	glUniform3fv(glGetUniformLocation(program, "viewpos"), 1, glm::value_ptr(cam + direction));
//glm::vec3 up = glm::cross(right, direction);

}
 


void createlight(float power, glm::vec3 direction, glm::vec3 color) {


}