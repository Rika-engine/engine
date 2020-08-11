#include <GL/glew.h>
#include <iostream>
#include  <GLFW/glfw3.h>
#include "mesh.h"
#include "audio.h"
#include "material.h"
#include "miscmethods.h"
#include "daeloader.h"
#include "mesh.h"
#include "ddsimporter.h"
#include "Model.h"
using namespace std;
int main() {

	int wd = 1024, wh = 1024;
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *window;
	
	window = glfwCreateWindow(wd, wh, "Engine", NULL, NULL);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	if (!window) {
		printf("could'nt oepn the window");
	}
	glViewport(0, 0, wd, wh);
	glfwMakeContextCurrent(window); 
	glewExperimental = GL_TRUE;
	glewInit();





	///TTTEEEEMPP{
	GLuint VBO;
	GLuint VAO;
		//temp 
	static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,1,0,0,
   1.0f, -1.0f, 0.0f,0,1,0,
   0.0f,  1.0f, 0.0f,0,0,1
	};




	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, 0, 6 * sizeof(float), (void*)(3*sizeof(GLfloat)));

	GLuint program;

program=bindshader();


glm::mat4 projmatrix=glm::perspective(glm::radians(45.0f),4.0f/3,0.1f,1000.0f);//45 degrees field of view,aspect ratio,field of view goes to 0.1 to 1000
glm::mat4 viewmatrix=glm::lookAt(glm::vec3(1,2,3), glm::vec3(0,0,0), glm::vec3(0,1,0));//the camera is at coordinates 1 2 3 ,looks at  the center\origin and is up (like an head)
//glm::mat4 projmatrix = glm::mat4(1);
//glm::mat4 viematrix = glm::mat4(1);




//	Mesh meshi;
	//meshi.a();
	do {
		GLuint combinedmatrixesid = glGetUniformLocation(program, "combinedmatrixes");
		glm::mat4 combinedmatrixes =   projmatrix*viewmatrix;
		glUniformMatrix4fv(combinedmatrixesid, 1, 0, &combinedmatrixes[0][0]);
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	meshi.process();
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glClearColor(0.2, 0, 0, 1);
		glfwPollEvents();
		glUseProgram(program);
		//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { window = false; }
		//} while (window);
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
}