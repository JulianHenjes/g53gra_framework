#include "Limb.h"
#include "../Engine/Engine.h"
#include <iostream>

//The "limb" of a more complex model, but can be used in isolation as a prop

Limb::Limb(const GLfloat* vertices_, const int* faces_, const GLfloat* normals_, int vertex_count_, int face_count_, GLuint texID_, const GLfloat* uvs_) :
	DisplayableObject()

{
	vertices = vertices_;
	faces = faces_;
	normals = normals_;
	vertex_count = vertex_count_;
	face_count = face_count_;
	uvs = uvs_;
	texID = texID_;
}


void Limb::Display() {

	//Set rotation for object
	glPushMatrix();
	glRotatef(rotation[0], 1, 0, 0);
	glRotatef(rotation[1], 0, 1, 0);
	glRotatef(rotation[2], 0, 0, 1);


	//Set Material Properties
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	//Faces and vertices and UV
	int vi[3];
	GLfloat v1, v2, v3, n1, n2, n3;
	GLfloat uv[3][2];
	GLfloat u, v;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);

	//std::cout << scale[0] << scale[1] << scale[2] << std::endl;
	
	//For every (tri) face
	for (int f = 0; f < face_count; f++) {

		glBegin(GL_TRIANGLES);

		/* Do some basic pointer maths to get the vertices and UV coordinates */

		//Get vertex index for each corner of tri
		vi[0] = *(faces + (f * 3));
		vi[1] = *(faces + (f * 3 + 1));
		vi[2] = *(faces + (f * 3 + 2));

		uv[0][0] = *(uvs + ((f * 3) * 2));
		uv[0][1] = *(uvs + ((f * 3) * 2 + 1));
		uv[1][0] = *(uvs + ((f * 3 + 1) * 2));
		uv[1][1] = *(uvs + ((f * 3 + 1) * 2 + 1));
		uv[2][0] = *(uvs + ((f * 3 + 2) * 2));
		uv[2][1] = *(uvs + ((f * 3 + 2) * 2 + 1));


		//For every corner
		for (int i = 0; i < 3; i++) {

			//Vertex for coordinate i
			v1 = *(vertices + (vi[i] * 3));
			v2 = *(vertices + (vi[i] * 3 + 1));
			v3 = *(vertices + (vi[i] * 3 + 2));

			//Normals for vertex i
			n1 = *(normals + (vi[i] * 3));
			n2 = *(normals + (vi[i] * 3 + 1));
			n3 = *(normals + (vi[i] * 3 + 2));

			//UV coordinates for vertex i
			u = uv[i][0];
			v = uv[i][1];

			//std::cout << u << ", " << v << std::endl;

			//Draw vertex
			glNormal3f(n1, n2, n3);
			glTexCoord2f(u,v);
			glVertex3f(v1 * scale[0] + pos[0], v2 * scale[1] + pos[1], v3 * scale[2] + pos[2]);

		}


		glEnd();

	}

	glBindTexture(GL_TEXTURE_2D,0);
	glDisable(GL_TEXTURE_2D);

	//Loop through child limbs and draw

	for (std::size_t i = 0; i < children.size(); ++i) {
		children[i]->Display();
	}

	glPopMatrix();

}

