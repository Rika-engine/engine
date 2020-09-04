#pragma once
 
Vertex loaddae(const char* path ,	std::vector <unsigned int> &index) {
	 
 
 
	Vertex  vertex;
	std::vector <glm::vec3> vertpox;
	std::vector <glm::vec2>UVs;
	std::vector <glm::vec3>normals;
	std::ifstream f;
	std::string s;
 
	f.open(path);
	if (f.is_open()) {


		while (getline(f, s)) {
			if (s.find("float_array id=") != -1) {
				std::printf("FOUND %s", s.c_str());
				if (s.find("POSITION") != -1) {
					printf("Position array");
					do {
						getline(f, s);
						float tempx = 2, tempy = 0, tempz = 0;

						if (sscanf(s.c_str(), "%f %f %f ", &tempx, &tempy, &tempz) == 3) {
						 

							vertpox.push_back(glm::vec3(tempx, tempy, tempz));
						 
						};
					 

						 
				 

					 

						if (s.find("</float_array>") != -1) {
						 

						}
					} while (s.find("</float_array>"));
					 
				}
				else if (s.find("Normal") != -1) {
				 
					do {
						getline(f, s);
						float tempx = 2, tempy = 0, tempz = 0;

						if (sscanf(s.c_str(), "%f %f %f ", &tempx, &tempy, &tempz) == 3) {
						 
							normals.push_back(glm::vec3(tempx, tempy, tempz));
						};
					 

					  
						if (s.find("</float_array>") != -1) {
						 

						}
					} while (s.find("</float_array>"));
				 

				}
				else if (s.find("UV") != -1) {
					printf("UVarray");
					do {
						getline(f, s);
						float tempx = 2, tempy = 0, tempz = 0;

						if (sscanf(s.c_str(), "%f %f  ", &tempx, &tempy ) == 2) {
						 
							UVs.push_back(glm::vec2(tempx, tempy));
						};
					 

						 
						 

				 
					 

						if (s.find("</float_array>") != -1) {
						 

						}
					} while (s.find("</float_array>"));
				 

				}
			}
			else if ((s.find("<triangles") != -1)|| (s.find("<polylist")))  {
			 
				short max=1; if (s.find("NORMAL") != -1) { printf("\n %d MAX\n",max);  max++; }
				if (s.find("TEXCOORD") != -1) { printf("\n %d MAX\n",max); max++; }
				if (s.find("COLOR") != -1) {  max++;  printf("\n%d MAX\n", max);
				}
			
				if (s.find("<p>") != -1) {
					
					vertex.normals.resize(normals.size() * sizeof(glm::vec3));
					vertex.uv.resize(UVs.size() * sizeof(glm::vec2)); std::printf(" INDICES  "); short i = 0;
					;
					vertex.position.resize(vertpox.size());
					vertex.position = vertpox;
					std::string s2; s2 = s.substr(s.find("<p>") + 3, s.length());;
			 
					char* c;
					c = strtok((char*)s2.c_str(), " <");	  index.push_back(atoi(c));
					i++; int ind=0;
					while (c = strtok(NULL, " <")) {

						s2 = c;
						if (s2.find("/p>") != -1) {
				 
							break;
						}
						else {
					 
							if (i == 0) {
								ind++;
							 
							 
								index.push_back(atoi(c));
					 
								i++;
								continue;
							}
							if (i == 3 && i <= max) {
							
								 

							 
								i = 0;
							}
							if (i == 2&& i<=max) {
								if (vertex.uv[index[ind]].x > 0 || (vertex.uv[index[ind]].y > 0)) {
								//	vertex.uv[index[ind]] = (vertex.uv[index[ind]] + UVs[atoi(c)]) / glm::vec2(2);
									normalize(vertex.uv[index[ind]] + UVs[atoi(c)]);
								}
 
								else {

									vertex.uv[index[ind]] = vertex.uv[index[ind]] + UVs[atoi(c)];


								}


 
								i++;

							}
							if (i == 1 && i <= max) {if(max==2){ vertex.uv[index[ind]] = UVs[atoi(c)]; i=0; }
							 


								if (vertex.normals[index[ind]].x >0 || (vertex.normals[index[ind]].y > 0)||(vertex.normals[index[ind]].z > 0)) {
									vertex.normals[index[ind]] = (vertex.normals[index[ind]] + normals[atoi(c)]) / glm::vec3(2);
								}
								 
							 
								vertex.normals[index[ind]] = (vertex.normals[index[ind]]+ normals[atoi(c)]) ;

								

							 
								 
								i++;

							}
						
							if (i >= max) {
								i = 0;
							}
						}
					 

					};

					 

				}

			}
		}
	
		 
	}
	else { std::printf("Unable to open .dae file %s", path); }
 
 
 std::printf("\n  END" );
	return vertex;

}