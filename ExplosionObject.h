#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "BaseObject.h"
#include "Common_Function.h"

const int EX_W = 145;
const int EX_H = 140;

class ExplosionObject : public BaseObject {
private :
	int frame;
	SDL_Rect clip[4];

public :
	ExplosionObject();
	~ExplosionObject();
	void set_clip();
	void set_frame(const int& fr) {
		frame = fr;
	}
	void showEx(SDL_Surface* des);


};


#endif