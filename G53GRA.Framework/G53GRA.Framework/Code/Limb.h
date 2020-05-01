#pragma once
#include "../Framework/Interface/DisplayableObject.h"
#include "../Framework/Interface/Animation.h"
#include <vector>

class Limb :
	public DisplayableObject, public Animation
{
public:
	Limb(const GLfloat* vertices_, const int* faces_, const GLfloat* normals_, int vertex_count_, int face_count_, GLuint texID_, const GLfloat* uvs_, const double* anim_);
	void Display();
	void addLimb(Limb* limb);
	void Update(const double& deltaTime);
	void setAnimSpeed(double animSpeed_);
	void setIgnoreLight(bool ignoreLight_);

private:
	//Geometry and Model Data
	const GLfloat* vertices;
	const int* faces;
	const GLfloat* normals;
	const GLfloat* uvs;
	const double* animation;
	int vertex_count;
	int face_count;
	GLuint texID;

	//Animation Settings
	double animSpeed = 100;
	double animTimer = 0;

	//Material Properties
	GLfloat diffuse[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specular[4] = { 0.3f,0.3f,0.3f,0.3f };
	GLfloat shininess[1] = { 30 };
	bool ignoreLight = false;

	//Child Limbs
	std::vector<Limb*> children = {};

};

