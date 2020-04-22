#include "GObj.h"

//Graphic Object Class


GObj::GObj() :
DisplayableObject()
{

}

void GObj::Display() {

}

void GObj::Update(const double& deltaTime)
{

}

void GObj::addLimb(Limb* limb)
{
	limbs.push_back(limb);
}
