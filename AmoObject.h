
#ifndef AMO_OBJECT_H_
#define AMO_OBJECT_H_
#include "BaseObject.h"

#define WIDTH_ONE 16
#define HEIGHT_ONE 5
#define WIDTH_BOOM 10
#define HEIGHT_BOOM 10

#define VELOCI_THREAT_AMO 7
#define VELOCI_MAIN_AMO 15

class AmoObject :public BaseObject {
private:
	int x_val;
	int y_val;
	bool is_move;
	int amo_type;

public:
	enum AmoType {
		NONE = 0,
		ONE = 1,
		BOOM = 2
	};
	AmoObject();
	~AmoObject();
	void HandleInputAction(SDL_Event events);
	void HandleMove(const int& x_border, const int& y_border);
	void HandleMoveR_to_L();

	int get_type() const {
		return amo_type;
	}
	void set_type(const int& type) {
		amo_type = type;
	}
	bool get_is_move() const {
		return is_move;
	}
	void set_is_move(bool is_move2) {
		is_move = is_move2;
	}
	void setWvH(const int& w, const int& h) {
		rect_.w = w;
		rect_.h = h;
	}
	void set_x_val(const int& val) {
		x_val = val;
	}
	void set_y_val(const int& val) {
		y_val = val;
	}

	int get_x_val() const {
		return x_val;

	}
	int get_y_val() const {
		return y_val;
	}


};

#endif