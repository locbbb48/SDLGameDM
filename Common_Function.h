
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<Windows.h>
#include<SDL.h>
#include<string>
#include<SDL_image.h>
#include<SDL_mixer.h>

const int SCO_W = 8000;

const int SC_W = 1450;
const int SC_H = 750;
const int SC_BPP = 32;
const int NUM_THREATS = 6;

static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkgr = NULL;
static SDL_Surface* g_bkgr2 = NULL;
static SDL_Event g_event;

static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];
static Mix_Music* g_sound_music;

namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(std::string file_path);
	void  ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void ApplySurfaceClip(SDL_Surface* scr, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	void  Cleanup();
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}
#endif