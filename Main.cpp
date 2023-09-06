
#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include <cstdlib>
#include <ctime>
#undef main

bool Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		return false;
	}

	g_screen = SDL_SetVideoMode(SC_W, SC_H, SC_BPP, SDL_SWSURFACE);
	
	if (g_screen == NULL) {
		return false;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		return false;
	}

	// Open file audio
	g_sound_bullet[0] = Mix_LoadWAV("Veo.wav");
	g_sound_bullet[1] = Mix_LoadWAV("Gun.wav");
	g_sound_exp[0] = Mix_LoadWAV("Firex2.wav");
	g_sound_exp[1] = Mix_LoadWAV("Explore.wav");
	/*g_sound_music = Mix_LoadMUS("Music_bgr.mp3");*/

	if (g_sound_exp[0] == NULL || g_sound_exp[1] == NULL || g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL /*|| g_sound_music == NULL*/) {
		return false;
	}

	return true;
	
}

int main(int arc, char* argv[]) {
	srand((unsigned int)time(NULL));

	bool is_run_scr = true;

	int backgr_x = 0;


	bool is_quit = 0;

	if (Init() == false) {
		return 0;
	}

	g_bkgr = SDLCommonFunc::LoadImage("Ice_bk_8000x850_2_2.png");
	if (g_bkgr == NULL) {
		return 0;
	}
	g_bkgr2 = SDLCommonFunc::LoadImage("Ice_bk_8000x850_2.png");
	if (g_bkgr2 == NULL) {
		return 0;
	}

	// Make MainObject
	MainObject human_object;
	// Rect Org
	human_object.SetRect(0, 0);
	bool ret = human_object.LoadImage2("plane86x37.png");
	if (!ret) {
		return 0;
	}

	// Init ExplosionObject
	ExplosionObject exp_main;
	ExplosionObject exp_threat;
	ret = exp_main.LoadImage2("Explore580x140.png");
	ret = exp_threat.LoadImage2("exp580x140.png");
	exp_main.set_clip();
	exp_threat.set_clip();
	if (ret == false) {
		return 0;
	}


	// Make ThreatObject
	ThreatObject* p_threats = new ThreatObject[NUM_THREATS];
	for (int t = 0; t < NUM_THREATS; t++) {
		ThreatObject* p_threat = p_threats + t;
		if (p_threat) {
			if (t % 3 == 0) {
				ret = p_threat->LoadImage2("plane95x45.png");
			}
			else {
				ret = p_threat->LoadImage2("plane85x38.png");
			}

			if (ret == false) {
				return 0;
			}

			// Randommmmmm
			int rand_y = rand() % 700;
			
			/*if (rand_y > SC_H - UNDER_LIMIT_THREAT) {
				rand_y = rand_y * t * 0.3;
			}*/
			int rand_x = rand() % 456;

			p_threat->SetRect(SC_W + t * 234 + 456, rand_y);
			// veloci threat
			p_threat->set_x_val(VELOCI_THREAT);
			AmoObject* p_amo = new AmoObject();
			p_threat->InitAmo(p_amo);
		}

	}

	while (!is_quit) {
		/*Mix_PlayMusic(g_sound_music, -1);*/
		
		while (SDL_PollEvent(&g_event)) {
			if (g_event.type == SDL_QUIT) {
				is_quit = true;
				break;
			}
			human_object.HandleInputAction(g_event, g_sound_bullet);
		}

		// Apply Babkground
		if (is_run_scr == true) {
			backgr_x -= 2;
			if (backgr_x <= -(SCO_W * 2 - SC_W)) {
				is_run_scr = false;
			}
			else {
				SDLCommonFunc::ApplySurface(g_bkgr, g_screen, backgr_x, 0);
				SDLCommonFunc::ApplySurface(g_bkgr2, g_screen, backgr_x + SCO_W, 0);
			}
		}
		else {
			SDLCommonFunc::ApplySurface(g_bkgr, g_screen, backgr_x, 0);
			SDLCommonFunc::ApplySurface(g_bkgr2, g_screen, backgr_x + SCO_W, 0);
		}

		// Run MainObject
		human_object.HandleMove();
		human_object.Show(g_screen);
		human_object.MakeAmo(g_screen);

		// Run ThreatObject
		for (int tt = 0; tt < NUM_THREATS; tt++) {
			ThreatObject* p_threat = p_threats + tt;
			if (p_threat) {
				p_threat->HandleMove(SC_W, SC_H);
				p_threat->Show(g_screen);
				p_threat->MakeAmo(g_screen, SC_W, SC_H);


				// Check collision MainO vs Threat
				bool is_coll = SDLCommonFunc::CheckCollision(human_object.GetRect(), p_threat->GetRect()); 
				if (is_coll) {

					for (int ex = 0; ex < 4; ex++) {
						int x_pos = human_object.GetRect().x + human_object.GetRect().w * 0.5 - EX_W * 0.5;
						int y_pos = human_object.GetRect().y + human_object.GetRect().h * 0.5 - EX_H * 0.5;

						int x_pos2 = p_threat->GetRect().x + p_threat->GetRect().w * 0.5 - EX_W * 0.5;
						int y_pos2 = p_threat->GetRect().y + p_threat->GetRect().h * 0.5 - EX_H * 0.5;

						exp_main.set_frame(ex);
						exp_main.SetRect(x_pos, y_pos);
						exp_main.showEx(g_screen);

						exp_threat.set_frame(ex);
						exp_threat.SetRect(x_pos2, y_pos2);
						exp_threat.showEx(g_screen);


						SDL_Delay(150);
						// Update Screen
						if (SDL_Flip(g_screen) == -1) {
							delete[] p_threat;
							SDLCommonFunc::Cleanup();
							return 0;
						}
					}

					Mix_PlayChannel(-1, g_sound_exp[1], 0);

					if (MessageBox(NULL, L"YOU LOSS (> <) GAME OVER", L"BTL_INFO", MB_OK) == IDOK) {
						delete[] p_threats;
						SDLCommonFunc::Cleanup();
						SDL_Quit();
						return 0;
					}
				}

				// Check collision AmoO vs Threat
				std::vector<AmoObject*> amo_list = human_object.GetAmoList();
				for (int am = 0; am < amo_list.size(); am++) {
					AmoObject* p_amo = amo_list.at(am);
					if (p_amo != NULL) {
						bool ret_coll = SDLCommonFunc::CheckCollision(p_amo->GetRect(), p_threat->GetRect());
						if (ret_coll) {
							for (int ex = 0; ex < 4; ex++) {
								int x_pos = p_threat->GetRect().x + p_threat->GetRect().w * 0.5 - EX_W * 0.5;
								int y_pos = p_threat->GetRect().y + p_threat->GetRect().h * 0.5 - EX_H * 0.5;

								exp_threat.set_frame(ex);
								exp_threat.SetRect(x_pos, y_pos);
								exp_threat.showEx(g_screen);
								
								// Update Screen
								if (SDL_Flip(g_screen) == -1) {
									delete[] p_threat;
									SDLCommonFunc::Cleanup();
									return 0;
								}
							}
							p_threat->Reset(SC_W + tt * 234 + 456);
							human_object.RemoveAmo(am);
							Mix_PlayChannel(-1, g_sound_exp[0], 0);
						}
					}
				}

				// Check collision MainO vs AmoTh
				std::vector<AmoObject*> amo_list2 = p_threat->GetAmoList();
				for (int im = 0; im < amo_list2.size(); im++) {
					AmoObject* p_amo = amo_list2.at(im);
					if (p_amo != NULL) {
						bool is_col = SDLCommonFunc::CheckCollision(human_object.GetRect(), p_amo->GetRect());
						if (is_col) {
							for (int ex = 0; ex < 4; ex++) {
								int x_pos = human_object.GetRect().x + human_object.GetRect().w * 0.5 - EX_W * 0.5;
								int y_pos = human_object.GetRect().y + human_object.GetRect().h * 0.5 - EX_H * 0.5;

								exp_main.set_frame(ex);
								exp_main.SetRect(x_pos, y_pos);
								exp_main.showEx(g_screen);


								SDL_Delay(150);
								// Update Screen
								if (SDL_Flip(g_screen) == -1) {
									return 0;
								}
							}

							Mix_PlayChannel(-1, g_sound_exp[1], 0);

							if (MessageBox(NULL, L"YOU LOSS (> <) GAME OVER", L"Bui_Thanh_Loc_INFO", MB_OK) == IDOK) {
								delete[] p_threats;
								SDLCommonFunc::Cleanup();
								SDL_Quit();
								return 0;
							}
						}
					}
				}
			}
		}

		// Update Screen
		if (SDL_Flip(g_screen) == -1) {
			return 0;
		}
	}
	delete[] p_threats;

	SDLCommonFunc::Cleanup();
	SDL_Quit();


	return 0;
}