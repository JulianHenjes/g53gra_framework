#pragma once
#include "../Framework/Interface/DisplayableObject.h"
#include "Animation.h"
#include "Limb.h"
#include <map>

class GObj :
	public DisplayableObject, public Animation
{
public:
	GObj();
	void addLimb(Limb* limb);
	void Display();
	void Update(const double& deltaTime);

private:
	//Limbs stored in vector
	std::vector<Limb*> limbs = {};
};

