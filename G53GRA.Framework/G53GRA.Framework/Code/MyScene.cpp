#include "MyScene.h"
#include "Prop.h"
#include "Limb.h"
#include "ModelManager.h"
#include "Spider.h"
#include "BeachBall.h"
#include "Mechanism.h"
#include <iostream>
#include <vector>


MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}



void MyScene::Initialise()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glutSetCursor(GLUT_CURSOR_NONE);

	ModelManager* mm = new ModelManager();
	Limb* limb;
	std::string modelname;
	
	//Get model for each model and pass into limb constructor, then pass into AddObjectToScene()
	modelname = "skybox";
	GLuint texture_skybox = Scene::GetTexture("Textures\\texture_skybox.bmp");
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
	GLuint texture_grass = Scene::GetTexture("Textures\\texture_grass.bmp");
	limb = new Limb(mm->getVertexPtr(modelname), mm->getFacePtr(modelname), mm->getNormalPtr(modelname), mm->getNumVertices(modelname), mm->getNumFaces(modelname), texture_grass, mm->getUvPtr(modelname), mm->getAnimPtr(modelname));
	limb->size(400);
	limb->position(0, -300, 0);
	limb->setIgnoreLight(true);
	AddObjectToScene(limb);



	addSpider(mm);
	addBeachBall(mm);
	addMechanism(mm);



	//Global Ambient Lighting Settings
	const GLfloat global_ambient[4] = { 0.f,0.f,0.f,1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	//GL_LIGHT0 Settings
	const GLfloat ambient[4] = { 0.22f,0.38f,0.61f,1.f }; //Blue ambient light -> sky
	const GLfloat diffuse[4] = { 0.8f,0.8f,0.6f,1.f }; //Yellow light -> sun
	const GLfloat specular[4] = { .2f,.2f,.2f,1.f }; //Bright white highlight
	const GLfloat position[4] = { 10000.f,10000.f,0.f,1.f };//W=1 -> Positional Light, //W=0 -> Directional Light
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

void MyScene::addMechanism(ModelManager* mm) {

	//Base Parts
	std::string modelname;
	Limb* parent;
	Limb* prevPart;
	Limb* part;
	int size = 30;
	GLuint texture_marble = Scene::GetTexture("Textures\\texture_procedural_marble.bmp");
	//Each piece happens to be the child of the previous one shaft <- turntable <- anubis_statue <- ankh
	std::vector<std::string> pieces = { "shaft", "turntable", "anubis_statue", "ankh" };
	//Positions of each piece relative to parent
	int positions[4][3] = { {0,30,0}, {0,30,0}, {0,180,0}, {-30,-55,-5} };

	//Create gearbox and crank, after this all remaining pieces are in a linear hierarchy so they can be added by iteration
	modelname = "gearbox";
	parent = new Limb(mm->getVertexPtr(modelname), mm->getFacePtr(modelname), mm->getNormalPtr(modelname), mm->getNumVertices(modelname), mm->getNumFaces(modelname), texture_marble, mm->getUvPtr(modelname), mm->getAnimPtr(modelname));
	parent->size(size);
	parent->position(400, -300, 400);
	
	//Crank, child of gearbox
	modelname = "crank";
	prevPart = new Limb(mm->getVertexPtr(modelname), mm->getFacePtr(modelname), mm->getNormalPtr(modelname), mm->getNumVertices(modelname), mm->getNumFaces(modelname), texture_marble, mm->getUvPtr(modelname), mm->getAnimPtr(modelname));
	prevPart->size(size);
	prevPart->position(57,95,0);

	//Create bevel_gear, remaining pieces are descendents of this one
	modelname = "bevel_gear";
	part = new Limb(mm->getVertexPtr(modelname), mm->getFacePtr(modelname), mm->getNormalPtr(modelname), mm->getNumVertices(modelname), mm->getNumFaces(modelname), texture_marble, mm->getUvPtr(modelname), mm->getAnimPtr(modelname));
	part->size(size);
	part->position(0, 125, 0);

	//Add defined parts
	parent->addLimb(prevPart);
	parent->addLimb(part);

	//Add other parts, where each is the child of the previous
	for (std::size_t i = 0; i < pieces.size(); ++i) {
		prevPart = part;
		modelname = pieces[i];
		part = new Limb(mm->getVertexPtr(modelname), mm->getFacePtr(modelname), mm->getNormalPtr(modelname), mm->getNumVertices(modelname), mm->getNumFaces(modelname), texture_marble, mm->getUvPtr(modelname), mm->getAnimPtr(modelname));
		part->size(size);
		part->position(positions[i][0],positions[i][1],positions[i][2]);
		prevPart->addLimb(part);
	}

	//Create Mechanism object and give it the model
	Mechanism* mech = new Mechanism(parent);
	AddObjectToScene(mech);

}

void MyScene::addBeachBall(ModelManager* mm) {

	std::string modelname = "beach_ball";
	Limb* ball;
	GLuint texture_ball = GetTexture("Textures\\texture_beach_ball.bmp");
	ball = new Limb(mm->getVertexPtr(modelname), mm->getFacePtr(modelname), mm->getNormalPtr(modelname), mm->getNumVertices(modelname), mm->getNumFaces(modelname), texture_ball, mm->getUvPtr(modelname), mm->getAnimPtr(modelname));
	ball->size(100);
	ball->position(30, -200, 30);
	BeachBall* beachBall = new BeachBall(ball);
	AddObjectToScene(beachBall);

}

void MyScene::addSpider(ModelManager* mm) {

	//Model parts
	std::string modelname = "spider_body";
	Limb* limb;
	Limb* body;
	GLuint texture_fur = Scene::GetTexture("Textures\\texture_fur_lowres.bmp");
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
