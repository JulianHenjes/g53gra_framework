#include "BeachBall.h"
#include <iostream>

BeachBall::BeachBall(Limb* model_) {
	model = model_;
}

void BeachBall::Display() {

	//Apply bounce and spin
	glPushMatrix();

	//Undo position to rotate around object centre
	glTranslatef(0, model->position()[1], 0);
	glTranslatef(0, height, 0);
	glRotatef(angle, 0, 1, 1);
	glTranslatef(0, -model->position()[1], 0);

	//Display model
	model->Display();

	glPopMatrix();
}

void BeachBall::Update(const double& deltaTime) {
	//Custom animation code
	//If ball is moving

	if ( vy != 0 && height != 0 ) {
		//Add vertical velocity to position
		height += vy*deltaTime;
		
		//Gravity
		vy = vy - 600 * deltaTime;
		spin = spin - deltaTime * spin;
		angle = angle + spin;
		//Keep angle in range 0 < angle < 360
		if (angle > 360) {
			angle = angle - 360;
		}


		//If ball below ground
		if (height < 0) {
			height = 0.1;

			if (vy < 0) {
				//Lose some kinetic energy with each bounce
				vy = -vy*0.4;
			}

			//If ball has lost most kinetic energy, bring to a halt
			if (vy < 10 && vy > -10 ) {
				vy = 0;
				height = 0;
			}

		}
		
	}

}


//Input handling
void BeachBall::HandleKey(unsigned char key, int state, int x, int y) {

	//std::cout << "pressed key " << key << std::endl;

	//Bounce the ball on the b key
	if (key == 'b' || key == 'B') {
		//std::cout << "height=" << height << ", vy=" << vy << std::endl;
		//If not moving and on ground
		if (vy == 0 && height == 0) {
			vy = 1000;
			height = 0.1;
			spin = 3;
		}

	}

}

void BeachBall::HandleSpecialKey(int key, int state, int x, int y) {

}

void BeachBall::HandleMouse(int button, int state, int x, int y) {

}

void BeachBall::HandleMouseDrag(int x, int y) {

}

void BeachBall::HandleMouseMove(int x, int y) {

}

