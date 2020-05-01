#pragma once
#include "../Framework/Interface/DisplayableObject.h"
#include "../Framework/Interface/Animation.h"
#include "Limb.h"

class Spider :
	public DisplayableObject, public Animation
{
public:
	Spider(Limb* model_);
	void Display();
	void Update(const double& deltaTime);
private:
	Limb* model;
	double animProgress = 0;
};

