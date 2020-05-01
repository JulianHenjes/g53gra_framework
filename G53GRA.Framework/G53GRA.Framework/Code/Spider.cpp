#include "Spider.h"
#include "../Engine/Engine.h"


Spider::Spider(Limb* model_) {
	model = model_;
}

void Spider::Display() {

	//Make the spider crawl in a circle
	glPushMatrix();
	glRotatef(animProgress,0,1,0);
	glTranslatef(0, 0, -300);

	model->Display();
	glPopMatrix();

}


void Spider::Update(const double& deltaTime) {

	//Make the animation loop every 360 degrees
	animProgress += deltaTime*50;
	if (animProgress > 360) {
		animProgress -= 360;
	}
	model->Update(deltaTime);

}
