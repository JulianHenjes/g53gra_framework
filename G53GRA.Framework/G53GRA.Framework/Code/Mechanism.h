#pragma once
#include "../Framework/Interface/DisplayableObject.h"
#include "../Framework/Interface/Animation.h"
#include "../Framework/Interface/Input.h"
#include "Limb.h"

class Mechanism :
	public DisplayableObject, public Animation, public Input
{
public:
	Mechanism(Limb* model);

	//Override from DisplayableObject
	void Display();

	//Override from Animation
	void Update(const double& deltaTime);

	//Override from Input
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);
	void HandleMouse(int button, int state, int x, int y);
	void HandleMouseDrag(int x, int y);
	void HandleMouseMove(int x, int y);

private:
	Limb* model;
	double animProgress = 0;
	bool turning = false;
};


