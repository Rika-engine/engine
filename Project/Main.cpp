#include "structs.h"
#include "libs.h"

 



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






	GLuint program;

program=bindshader("Vertexshader.glsl", "Fragmentshader.glsl");
GLuint lampprogram= bindshader("lampvshader.glsl", "lampfshader.glsl");

glm::mat4 projmatrix=glm::perspective(glm::radians(45.0f),4.0f/3,0.1f,1000.0f);//45 degrees field of view,aspect ratio,field of view goes to 0.1 to 1000
//glm::mat4 viewmatrix=glm::lookAt(glm::vec3(1,2,3), glm::vec3(0,0,0), glm::vec3(0,1,0));//the camera is at coordinates 1 2 3 ,looks at  the center\origin and is up (like an head)
//glm::mat4 projmatrix = glm::mat4(1);
//glm::mat4 viematrix = glm::mat4(1);
glm::mat4 viewmatrix = glm::mat4(1);

glm::vec3 camerapos(-12, 0, 0);
//	Mesh meshi;
	//meshi.a();
glm::vec3 lightpos(0,0,0);

//Mesh mesh2("g3.dae");
 
//Mesh mesh2("plane.dae");
Mesh meshi("strangeflower", glm::vec3(-0, 0, 0));
Mesh mesh("container", lightpos);
Mesh mesh2("container", glm::vec3(1,2,3));
Mesh mesh3("heart", glm::vec3(-1, -2, -3));
//glUniform3f(glGetUniformLocation(program, "lightpos"), lightpos.x, lightpos.y, lightpos.z);

/*

Mesh mesh6("cube.dae", glm::vec3(0, 0, 5));
Mesh mesh5("cube.dae", glm::vec3(0, 0, -5));
Mesh mesh8("cube.dae", glm::vec3(0, -6, 0));
Mesh mesh3("cube.dae", glm::vec3(5,  0, 0));
Mesh mesh4("cube.dae", glm::vec3(-5, 0, 4));
 */
// Mesh mesh22("sad.dae", glm::vec3(0, -2, 12));
 
do {


	//TEMP

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		lightpos.x-=0.03;
		mesh.translate(glm::vec3(0.03, 0,0));

	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		lightpos.x += 0.03;
		mesh.translate(glm::vec3(-0.03, 0, 0));

	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		lightpos.z += 0.03;
		mesh.translate(glm::vec3(0, 0, 0.03));

	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		lightpos.z -= 0.03;
		mesh.translate(glm::vec3(0, 0,- 0.03));

	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		lightpos.y += 0.03;
		mesh.translate(glm::vec3(0,   0.03,0));

	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
		lightpos.y -= 0.03;
		mesh.translate(glm::vec3(0,  -0.03,0));

	}

	cameramovmnt(program,window, wd, wh, camerapos,viewmatrix);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);
	//	glFrontFace(GL_CW);
		glUseProgram(program);
		glUniform3fv(glGetUniformLocation(program, "lightpos"), 1, glm::value_ptr(lightpos));
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
		 meshi.process( program,projmatrix,viewmatrix);
		 mesh2.process(program, projmatrix, viewmatrix);
		 mesh3.process(program, projmatrix, viewmatrix);
	   	mesh.process(lampprogram, projmatrix, viewmatrix);
 /*	
 mesh3.process(program);
 mesh4.process(program);
 mesh6.process(program);
 mesh5.process(program);
 mesh8.process(program);
 */
	//	meshi.process();
	//	glEnableVertexAttribArray(0);
	//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
		

	//	glDrawArrays(GL_TRIANGLES, 0, 444);
	//	glDrawElements(GL_TRIANGLES, index.size()*sizeof(int) , GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glClearColor(0.1, 0.1, 0.1, 1);
		glfwPollEvents();
		
		//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { window = false; }
		//} while (window);
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
}