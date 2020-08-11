#pragma once
#include <vector>
#include  <glm.hpp>
#include <gtc/matrix_transform.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normals;
};
class Mesh {
	std::vector<Vertex> vertici;
	std::vector<int>index;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	glm::mat4 matrix;
public:
	Mesh();
	void a(){




		//temp 
		static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
		};




		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, 0);

	
	
	}
	void rotate(glm::vec3);
	void translate(glm::vec3 );
	void scale(glm::vec3 );
	void process();
};
Mesh::Mesh() {




	//temp 
	static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
	};




	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, 0);


/**/
}void Mesh:: process(){
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
	glDrawArrays(GL_TRIANGLES,0, 3);

}
void Mesh:: rotate(glm::vec3 rotation) {
	//matrix = glm::rotate(matrix, glm::radians(value));

}
void Mesh::translate(glm::vec3 translation) {
	matrix = glm::translate(matrix, translation);
}
void Mesh::scale(glm::vec3 scale) {
	matrix = glm::scale(matrix, scale);

}