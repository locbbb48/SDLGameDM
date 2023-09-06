#include "ExplosionObject.h"

ExplosionObject::ExplosionObject() {

}

ExplosionObject::~ExplosionObject() {

}

void ExplosionObject::set_clip() {
	clip[0].x = 0;
	clip[0].y = 0;
	clip[0].w = EX_W;
	clip[0].h = EX_H;

	clip[1].x = EX_W;
	clip[1].y = 0;
	clip[1].w = EX_W;
	clip[1].h = EX_H;

	clip[2].x = 2*EX_W;
	clip[2].y = 0;
	clip[2].w = EX_W;
	clip[2].h = EX_H;

	clip[3].x = 3 * EX_W;
	clip[3].y = 0;
	clip[3].w = EX_W;
	clip[3].h = EX_H;
}

void ExplosionObject::showEx(SDL_Surface* des) {
	if (frame >= 4) {
		frame = 0;
	}

	SDLCommonFunc::ApplySurfaceClip(this->p_object_, des, &clip[frame], rect_.x, rect_.y);
}