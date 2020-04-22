#pragma once
#include "../Framework/Interface/DisplayableObject.h"
#include <vector>

class Limb :
	public DisplayableObject
{
public:
	Limb(const GLfloat* vertices_, const int* faces_, const GLfloat* normals_, int vertex_count_, int face_count_, GLuint texID_, const GLfloat* uvs_);
	void Display();
private:
	//Geometry
	const GLfloat* vertices;
	const int* faces;
	const GLfloat* normals;
	const GLfloat* uvs;
	int vertex_count;
	int face_count;
	GLuint texID;

	//Material Properties
	GLfloat diffuse[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specular[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat shininess[1] = { 30 };

	//Child Limbs
	std::vector<Limb*> children = {};

};

