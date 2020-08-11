#pragma once
#include <string>
#include <fstream>
GLuint bindshader() {
	std::string s,s2;
	GLuint vertexshaderid= glCreateShader(GL_VERTEX_SHADER);;
	GLuint fragmentshaderid= glCreateShader(GL_FRAGMENT_SHADER);;
//	ifstream files("Vertexshader.glgl",ios::in);
	std:: ifstream f;
	f.open("Vertexshader.glsl");
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

	f.open("Fragmentshader.glsl");
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
void cameramovmnt() {


}