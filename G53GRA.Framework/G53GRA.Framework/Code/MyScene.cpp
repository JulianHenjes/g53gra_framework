#include "MyScene.h"
#include "Prop.h"
#include "Limb.h"
#include "GObj.h"
#include "ModelManager.h"
#include <iostream>

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

/*

TO DO LIST
 - add hierarchy support to Limb
 - add animation support to GObj (animate from GObj, but Limb does the actual drawing)
	(animations can be a fixed number of keyframes, and speed determined separately)
 - create some not-buggy lighting (move to where sun is approx)
 - create sand dunes and (animated?) grass
 - add player model to user control
 - add 3rd person camera or top-down wide-angle view
	(switch using keypresses)
 - add 2 other complex realistic models (people on the beach? procedural (hierarchical) trees?)

 */

void MyScene::Initialise()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glutSetCursor(GLUT_CURSOR_NONE);

	ModelManager* mm = new ModelManager();
	Limb* limb;
	std::string modelname;
	
	//Get model for each model and pass into limb constructor, then pass into AddObjectToScene();
	modelname = "spider_body";
	GLuint texture_fur = Scene::GetTexture("C:/Users/hench/Desktop/Documents/University/Graphics/texture_fur.bmp");
	limb = new Limb(mm->getVertexPtr(modelname), mm->getFacePtr(modelname), mm->getNormalPtr(modelname), mm->getNumVertices(modelname), mm->getNumFaces(modelname), texture_fur, mm->getUvPtr(modelname));
	limb->size(100);
	limb->orientation(0, 0, 90);
	AddObjectToScene(limb);

	modelname = "skybox";
	GLuint texture_skybox = Scene::GetTexture("C:/Users/hench/Desktop/Documents/University/Graphics/texture_skybox.bmp");
	limb = new Limb(mm->getVertexPtr(modelname), mm->getFacePtr(modelname), mm->getNormalPtr(modelname), mm->getNumVertices(modelname), mm->getNumFaces(modelname), texture_skybox, mm->getUvPtr(modelname));
	limb->size(10000);
	limb->position(0, 0, 0);
	AddObjectToScene(limb);



	//Camera was way too fast so I set the speed from 1.0f to 0.1f in Camera.cpp as there was no
	//method to set the speed

	//Global Ambient Lighting Settings
	const GLfloat global_ambient[4] = { 1.f,1.f,1.f,1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	//GL_LIGHT0 Settings
	const GLfloat ambient[4] = { 0.15f,0.15f,0.15f,1.f }; //Blue ambient light -> sky
	const GLfloat diffuse[4] = { 0.2f,0.2f,0.2f,1.f }; //Yellow light -> sun
	const GLfloat specular[4] = { 1.f,1.f,1.f,1.f }; //Bright white highlight
	const GLfloat position[4] = { 0.f,0.f,0.f,1.f };//W=1 -> Positional Light, //W=0 -> Directional Light

	//Replace Default Light
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	

}

void MyScene::Projection()
{
	glMatrixMode(GL_PROJECTION);

	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 100000.0);
}
