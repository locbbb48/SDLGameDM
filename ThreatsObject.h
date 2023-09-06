
#ifndef THREATS_OBJECTS_H_
#define THREATS_OBJECTS_H_
#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>

#define WIDTH_THREAT 95
#define HEIGHT_THREAT 45
#define VELOCI_THREAT 3

const int UNDER_LIMIT_THREAT = 150;

class ThreatObject : public BaseObject {
public:
	ThreatObject();
	~ThreatObject();

	void HandleMove(const int& x_border, const int& y_border);
	void HandleInputAction(SDL_Event events);

	void set_x_val(const int& val) {
		x_val = val;
	}
	void set_y_val(const int& val) {
		y_val = val;
	}
	int get_x_val() {
		return x_val;
	}
	int get_y_val() {
		return y_val;
	}

	void setAmoList(std::vector<AmoObject*> amo_list) {
		p_amo_list = amo_list;
	}
	std::vector<AmoObject*> GetAmoList() const {
		return p_amo_list;
	}
	void InitAmo(AmoObject* p_amo);
	void MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit);
	void Reset(const int& x_boder);
	void ResetAmo(AmoObject* p_amo);

private:
	int x_val;
	int y_val;

	std::vector<AmoObject*> p_amo_list;
};

#endif