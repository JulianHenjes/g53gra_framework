#pragma once
#include <string>
#include <map>
#include "../Engine/Engine.h"

class ModelManager
{
public:
	ModelManager();
	const GLfloat* getVertexPtr(std::string modelname);
	const GLfloat* getNormalPtr(std::string modelname);
	const GLfloat* getUvPtr(std::string modelname);
	const int* getFacePtr(std::string modelname);
	int getNumVertices(std::string modelname);
	int getNumFaces(std::string modelname);
private:
	std::map<std::string, const GLfloat*> vertex_data;
	std::map<std::string, const GLfloat*> normal_data;
	std::map<std::string, const int*> face_data;
	std::map<std::string, const GLfloat*> uv_data;
	std::map<std::string, int> num_vertices;
	std::map<std::string, int> num_faces;
};

