
#include "MainObject.h"

MainObject::MainObject() {
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val = 0;
	y_val = 0;
}

MainObject::~MainObject() { ; }

void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2]) {
	if (events.type == SDL_KEYDOWN) {
		switch (events.key.keysym.sym)
		{
		case SDLK_w:
			y_val -= SPEED_UnD;

			break;
		case SDLK_s:
			y_val += SPEED_UnD;

			break;
		case SDLK_d:
			x_val += SPEED_RnL;

			break;
		case SDLK_a:
			x_val -= SPEED_RnL;

			break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP) {
		switch (events.key.keysym.sym) {
		case SDLK_w: y_val += SPEED_UnD;
			break;
		case SDLK_s: y_val -= SPEED_UnD;
			break;
		case SDLK_a: x_val += SPEED_RnL;
			break;
		case SDLK_d: x_val -= SPEED_RnL;
			break;
		}
	}
	else if (events.type == SDL_MOUSEBUTTONDOWN) {
		AmoObject* p_amo = new AmoObject();
		if (events.button.button == SDL_BUTTON_LEFT) {
			p_amo->setWvH(WIDTH_ONE, HEIGHT_ONE);
			p_amo->LoadImage2("amo20x10.png");
			p_amo->set_type(AmoObject::ONE);
			Mix_PlayChannel(-1, bullet_sound[0], 0);
		}
		else if (events.button.button == SDL_BUTTON_RIGHT) {
			p_amo->setWvH(WIDTH_BOOM, HEIGHT_BOOM);
			p_amo->LoadImage2("boom10x10.png");
			p_amo->set_type(AmoObject::BOOM);
			Mix_PlayChannel(-1, bullet_sound[1], 0);
		}

		p_amo->SetRect(this->rect_.x + 75, this->rect_.y + 33);
		p_amo->set_is_move(true);
		p_amo->set_x_val(VELOCI_MAIN_AMO);
		p_amo_list.push_back(p_amo);


	}
	else if (events.type == SDL_MOUSEBUTTONUP) {

	}
	else {

	}
}

void MainObject::MakeAmo(SDL_Surface* des) {
	for (int i = 0; i < p_amo_list.size(); i++) {
		AmoObject* p_amo = p_amo_list.at(i);
		if (p_amo != NULL) {
			if (p_amo->get_is_move()) {
				p_amo->HandleMove(SC_W, SC_H);
				p_amo->Show(des);
			}
			else {
				if (p_amo != NULL) {
					p_amo_list.erase(p_amo_list.begin() + i);
					delete p_amo;
					p_amo = NULL;
				}
			}
		}
	}
}

void MainObject::HandleMove() { 
	rect_.x += x_val;
	if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SC_W) {
		rect_.x -= x_val;
	}

	rect_.y += y_val;
	if (rect_.y < 0 || rect_.y + WIDTH_MAIN_OBJECT > 750) {
		rect_.y -= y_val;
	}

}

void MainObject::RemoveAmo(const int& idx) {
	for (int i = 0; i < p_amo_list.size(); i++) {
		if (idx < p_amo_list.size()) {
			AmoObject* p_amo = p_amo_list.at(idx);
			p_amo_list.erase(p_amo_list.begin() + idx);

			if (p_amo != NULL) {
				delete p_amo;
				p_amo = NULL;
			}
		}
	}
}