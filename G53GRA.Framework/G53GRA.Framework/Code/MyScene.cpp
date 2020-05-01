#include "MyScene.h"
#include "Prop.h"
#include "Limb.h"
#include "ModelManager.h"
#include "Spider.h"
#include <iostream>
#include <vector>


MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

/*

TO DO LIST

 - add 3rd person camera and/or top-down wide-angle view
	(switch using keypresses)
	subclass Camera() and override HandleMouse()
 - support exporting limb offsets
 - add 2 other complex realistic models (people on the beach? procedural (hierarchical) trees?)
 - add player model to user control (armour?)

 */

void MyScene::Initialise()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glutSetCursor(GLUT_CURSOR_NONE);

	ModelManager* mm = new ModelManager();
	Limb* limb;
	std::string modelname;
	
	//Get model for each model and pass into limb constructor, then pass into AddObjectToScene()
	modelname = "skybox";
	GLuint texture_skybox = Scene::GetTexture("C:/Users/hench/Desktop/Documents/University/Graphics/texture_skybox.bmp");
	limb = new Limb(mm->getVertexPtr(modelname), mm->getFacePtr(modelname), mm->getNormalPtr(modelname), mm->getNumVertices(modelname), mm->getNumFaces(modelname), texture_skybox, mm->getUvPtr(modelname), mm->getAnimPtr(modelname));
	limb->size(10000);
	limb->position(0, 0, 0);
	limb->setIgnoreLight(true);
	AddObjectToScene(limb);

	modelname = "ground";
	limb = new Limb(mm->getVertexPtr(modelname), mm->getFacePtr(modelname), mm->getNormalPtr(modelname), mm->getNumVertices(modelname), mm->getNumFaces(modelname), texture_skybox, mm->getUvPtr(modelname), mm->getAnimPtr(modelname));
	limb->size(400);
	limb->position(0, -300, 0);
	limb->setIgnoreLight(true);
	AddObjectToScene(limb);


	modelname = "grass_cluster";
	GLuint texture_grass = Scene::GetTexture("C:/Users/hench/Desktop/Documents/University/Graphics/texture_grass.bmp");
	limb = new Limb(mm->getVertexPtr(modelname), mm->getFacePtr(modelname), mm->getNormalPtr(modelname), mm->getNumVertices(modelname), mm->getNumFaces(modelname), texture_grass, mm->getUvPtr(modelname), mm->getAnimPtr(modelname));
	limb->size(400);
	limb->position(0, -300, 0);
	limb->setIgnoreLight(true);
	AddObjectToScene(limb);



	addSpider(mm);


	//Camera was way too fast so I set the speed from 1.0f to 0.1f in Camera.cpp as there was no
	//method to set the speed

	//Global Ambient Lighting Settings
	const GLfloat global_ambient[4] = { 0.f,0.f,0.f,1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	//GL_LIGHT0 Settings
	const GLfloat ambient[4] = { 0.22f,0.38f,0.61f,1.f }; //Blue ambient light -> sky
	const GLfloat diffuse[4] = { 0.8f,0.8f,0.6f,1.f }; //Yellow light -> sun
	const GLfloat specular[4] = { .2f,.2f,.2f,1.f }; //Bright white highlight
	const GLfloat position[4] = { 1000.f,1000.f,0.f,1.f };//W=1 -> Positional Light, //W=0 -> Directional Light
	//Replace Default Light
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	//GL_LIGHT1 Settings
	const GLfloat ambient2[4] = { 1.f,1.f,1.f,1.f };
	const GLfloat diffuse2[4] = { 0.f,0.f,0.f,0.f }; 
	const GLfloat specular2[4] = { 0.f,0.f,0.f,0.f };
	const GLfloat position2[4] = { 0.f,0.f,0.f,0.f };
	//Replace Default Light
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular2);
	glLightfv(GL_LIGHT1, GL_POSITION, position2);


}



void MyScene::addSpider(ModelManager* mm) {

	//Model parts
	std::string modelname = "spider_body";
	Limb* limb;
	Limb* body;
	GLuint texture_fur = Scene::GetTexture("C:/Users/hench/Desktop/Documents/University/Graphics/texture_fur_lowres.bmp");
	std::vector<std::string> pieces = { "spider_back","spider_leg_r_1","spider_leg_r_2" ,"spider_leg_r_3" ,"spider_leg_r_4","spider_leg_l_1","spider_leg_l_2" ,"spider_leg_l_3" ,"spider_leg_l_4" };

	//Create body (parent for all other limbs)
	body = new Limb(mm->getVertexPtr(modelname), mm->getFacePtr(modelname), mm->getNormalPtr(modelname), mm->getNumVertices(modelname), mm->getNumFaces(modelname), texture_fur, mm->getUvPtr(modelname), mm->getAnimPtr(modelname));
	body->size(40);
	body->position(0, -230, 0);

	//Add other limbs as children
	for (std::size_t i = 0; i < pieces.size(); ++i) {
		modelname = pieces[i];
		limb = new Limb(mm->getVertexPtr(modelname), mm->getFacePtr(modelname), mm->getNormalPtr(modelname), mm->getNumVertices(modelname), mm->getNumFaces(modelname), texture_fur, mm->getUvPtr(modelname), mm->getAnimPtr(modelname));
		limb->size(40);
		limb->setAnimSpeed(500);
		body->addLimb(limb);
	}

	//Create spider object and give it the model
	Spider* spider = new Spider(body);
	AddObjectToScene(spider);

}

void MyScene::Projection()
{
	glMatrixMode(GL_PROJECTION);

	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 100000.0);
}
