#include "Prop.h"
#include "../Engine/Engine.h"
#include <iostream>

//DEPRECATED, use Limb now
//Class for assets that don't have any complex behaviours
//Draws a placeholder triangle, subclass from it

Prop::Prop()
	: DisplayableObject()
{
}

void Prop::Display() {

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	//For every tri of the mesh
	for (int i = 0; i < (sizeof(faces) / sizeof(*faces)); i++) {

		//Draw Faces (All Meshes Must Be Triangulated)
		glBegin(GL_TRIANGLES);//GL_TRIANGLES or GL_LINES

		glNormal3f(normals[faces[i][0]][0], normals[faces[i][0]][1], normals[faces[i][0]][2] );
		glVertex3f(vertices[faces[i][0]][0] * scale[0], vertices[faces[i][0]][1] * scale[1], vertices[faces[i][0]][2] * scale[2]);
		glNormal3f(normals[faces[i][1]][0], normals[faces[i][1]][1], normals[faces[i][1]][2]);
		glVertex3f(vertices[faces[i][1]][0] * scale[0], vertices[faces[i][1]][1] * scale[1], vertices[faces[i][1]][2] * scale[2]);
		glNormal3f(normals[faces[i][2]][0], normals[faces[i][2]][1], normals[faces[i][2]][2]);
		glVertex3f(vertices[faces[i][2]][0] * scale[0], vertices[faces[i][2]][1] * scale[2], vertices[faces[i][2]][2] * scale[2]);
		//If drawing wireframe, connect back to first coordinate
//		glVertex3f(vertices[faces[i][0]][0] * scale[0], vertices[faces[i][0]][1] * scale[1], vertices[faces[i][0]][2] * scale[2]);

		glEnd();


	}


	//For Debugging
//	std::cout << "Drawn Prop" << std::endl;

}
