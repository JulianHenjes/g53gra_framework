#include "Mechanism.h"


Mechanism::Mechanism(Limb* model_) {
	model = model_;
}

void Mechanism::Display() {
	model->Display();
}

void Mechanism::Update(const double& deltaTime) {

	//Only update the animation while flag is set
	if (turning) {
		model->Update(deltaTime);
	}

}


//Input Control
void Mechanism::HandleKey(unsigned char key, int state, int x, int y) {
	//1 if down, 0 if up

	//Keep turning = true while 't' key is pressed
	if (key == 't' || key == 'T') {
		if (state == 1)
			turning = true;
		if (state == 0)
			turning = false;
	}
}
void Mechanism::HandleSpecialKey(int key, int state, int x, int y) {

}
void Mechanism::HandleMouse(int button, int state, int x, int y) {

}
void Mechanism::HandleMouseDrag(int x, int y) {

}

void Mechanism::HandleMouseMove(int x, int y) {

}

