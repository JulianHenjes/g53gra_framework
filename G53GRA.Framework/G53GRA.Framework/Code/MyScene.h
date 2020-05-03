#pragma once
#include "../Framework/Engine/Scene.h"
#include "ModelManager.h"


class MyScene :
	public Scene
{
public:
	MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	~MyScene() {};

private:
	void Initialise();
	void addMechanism(ModelManager* mm);
	void addBeachBall(ModelManager* mm);
	void Projection();
	void addSpider(ModelManager* mm);

};