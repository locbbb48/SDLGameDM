
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "Common_Function.h"

class BaseObject
{
protected:
	SDL_Rect rect_;
	SDL_Surface* p_object_;

public:
	BaseObject();
	~BaseObject();
	void Show(SDL_Surface* des);
	bool LoadImage2(const char* file_name);

	void SetRect(const int& x, const int& y) {
		rect_.x = x;
		rect_.y = y;
	}
	SDL_Rect GetRect() {
		return rect_;
	}
	SDL_Surface* GetObject(){
		return p_object_;
	}

};

#endif


;