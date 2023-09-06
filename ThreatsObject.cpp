
#include "ThreatsObject.h"



ThreatObject::ThreatObject() {
	rect_.x = SC_W;
	rect_.y = SC_H*0.3;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;

	x_val = 0;
	y_val = 0;
}

ThreatObject::~ThreatObject() {
	if (p_amo_list.size() > 0) {
		for (int i = 0; i < p_amo_list.size(); i++) {
			AmoObject* p_amo = p_amo_list.at(i);
			if (p_amo != NULL) {
				delete p_amo;
				p_amo = NULL;
			}
		}
		p_amo_list.clear();
	}
}

void ThreatObject::InitAmo(AmoObject* p_amo) {
	if (p_amo) {
		bool ret = p_amo->LoadImage2("bullet16x5.png");
		if (ret) {
			p_amo->set_is_move(true);
			p_amo->setWvH(16, 5);
			p_amo->set_type(AmoObject::ONE);
			p_amo->SetRect(rect_.x+15, rect_.y + rect_.h * 0.3 +24);
			p_amo_list.push_back(p_amo);
		}
	}
}

void ThreatObject::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit) {
	for (int i = 0; i < p_amo_list.size(); i++) {
		AmoObject* p_amo = p_amo_list.at(i);
		if (p_amo) {
			if (p_amo->get_is_move()) {
				p_amo->Show(des);
				p_amo->HandleMoveR_to_L();
			}
			else {
				p_amo->set_is_move(true);
				p_amo->SetRect(rect_.x + 15, rect_.y + rect_.h*0.3 + 24);
			}
		}

	}
}

void ThreatObject::HandleMove(const int& v_border, const int& y_border) {
	rect_.x -= x_val;
	if (rect_.x < 0) {
		rect_.x = SC_W;
		int rand_y = rand()% 700;
		/*if (rand_y > SC_H - UNDER_LIMIT_THREAT) {
			rand_y = SC_H * 0.3;
		}*/
		rect_.y = rand_y;
	}

}

void ThreatObject::HandleInputAction(SDL_Event events) {}

void ThreatObject::Reset(const int& x_boder) {
	rect_.x = x_boder;
	int rand_y = rand() % 700;
	/*if (rand_y > SC_H - UNDER_LIMIT_THREAT) {
		rand_y = SC_H * 0.3;
	}*/
	rect_.y = rand_y;

	for (int i = 0; i < p_amo_list.size(); i++) {
		AmoObject* p_amo = p_amo_list.at(i);
		if (p_amo) {
			ResetAmo(p_amo);
		}
	}
}

void ThreatObject::ResetAmo(AmoObject* p_amo) {
	p_amo->SetRect(rect_.x, rect_.y + rect_.h * 0.3);
}