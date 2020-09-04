#pragma once

class Mesh {
	Vertex vertici;
	std::vector< unsigned int>index;
	GLuint VAO;
	GLuint VBO, VBO2,VBO3;
	GLuint EBO;
	GLuint textureid;
	glm::mat4 modelmatrix;
public:
	Mesh(const char* name,glm::vec3 position) {
		std::string fullpath = "C:\\Users\\Rika\\Desktop\\project\\models\\"  ;
			fullpath=fullpath+name+"\\"+name+".dae";
	
	 	vertici = loaddae(fullpath.c_str(),  index);
 

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		modelmatrix = glm::mat4(1);
		for (int i = 0; i < index.size(); i++) {
	 
		}









		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);


		glBufferData(GL_ARRAY_BUFFER, vertici.position.size() * sizeof(glm::vec3), vertici.position.data(), GL_STATIC_DRAW);
		 
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
		glEnableVertexAttribArray(0);

		 

		glGenBuffers(1, &VBO2);
		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
		glBufferData(GL_ARRAY_BUFFER, vertici.uv.size() * sizeof(glm::vec2), vertici.uv.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
		glVertexAttribPointer(
			1,                                 
			2,                              
			GL_FLOAT,                         
			GL_FALSE,                       
			0,                               
			(void*)0                          
		);
 

	 glGenBuffers(1, &VBO3);
		glBindBuffer(GL_ARRAY_BUFFER, VBO3);
		glBufferData(GL_ARRAY_BUFFER, vertici.normals.size() * sizeof(glm::vec3), vertici.normals.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
		glVertexAttribPointer(
			2,                                 
			3,                                
			GL_FLOAT,                         
			GL_FALSE,                         
			0,                               
			(void*)0                           
		);



		glGenBuffers(1, &EBO);




		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
 
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), index.data(), GL_STATIC_DRAW);


		glBindVertexArray(0);
		loadtexture(name,textureid);


	 
		translate(position);
 





		 





	} 

 
	void rotate(glm::vec3);
	void translate(glm::vec3 transl);
	void scale(glm::vec3 );
	void process(GLuint program, glm::mat4& projmatrix, glm::mat4& viewmatrix);
};
 
void Mesh:: process(GLuint program,glm::mat4 &projmatrix,glm::mat4 &viewmatrix){
	glEnable(GL_CULL_FACE);
//	glCullFace(GL_FRONT);
//	glFrontFace(GL_CW);
	glEnable(GL_BLEND);

	glUseProgram(program);
	GLuint combinedmatrixesid = glGetUniformLocation(program, "combinedmatrixes");

	glm::mat4 combinedmatrixes = projmatrix * viewmatrix;
	glUniformMatrix4fv(combinedmatrixesid, 1, 0, &combinedmatrixes[0][0]);
	GLuint modelmatrixid = glGetUniformLocation(program, "modelmatrix");
	glUniformMatrix4fv(modelmatrixid, 1, 0, &modelmatrix[0][0]);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnableVertexAttribArray(0);
	glBindTexture(GL_TEXTURE_2D, textureid);
	glActiveTexture(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBindVertexArray(VAO);

 glDrawElements(GL_TRIANGLES, index.size() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);
 

}
void Mesh:: rotate(glm::vec3 rotation) {
 modelmatrix = glm::rotate(modelmatrix, glm::radians(rotation.x),glm::vec3(1,0,0));
 modelmatrix = glm::rotate(modelmatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
 modelmatrix = glm::rotate(modelmatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
}
void Mesh::translate(glm::vec3 translation) {
	modelmatrix = glm::translate(modelmatrix, translation);
}
void Mesh::scale(glm::vec3 scale) {
	modelmatrix = glm::scale(modelmatrix, scale);

}