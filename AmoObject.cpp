
#include "AmoObject.h"

AmoObject::AmoObject() {
	rect_.x = 0;
	rect_.y = 0;
	x_val = 0;
	y_val = 0;
	amo_type = NONE;
	is_move = false;

}

AmoObject::~AmoObject() {}

void AmoObject::HandleMove(const int& x_border, const int& y_border) {
	// veloci amoobject
	rect_.x += x_val;
	if (rect_.x > x_border) {
		is_move = false;
	}
}

void AmoObject::HandleMoveR_to_L() {
	// veloci 
	rect_.x -= VELOCI_THREAT_AMO;
	if (rect_.x < 0) {
		is_move = false;
	}
}

void AmoObject::HandleInputAction(SDL_Event events) {

	//todo
}