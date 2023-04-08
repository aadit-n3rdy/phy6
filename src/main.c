#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "SDL_FontCache.h"

#include "vec2.h"
#include "charge.h"
#include "state.h"
#include "loader.h"
#include "view.h"

#define WIN_WIDTH	800
#define WIN_HEIGHT	600

int main(int argc, char **argv) {

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	struct view cam;
	cam.scale = 10;
	cam.pos = (vec2_t){0, 0};

	char *fname;

	if (argc > 1) {
		fname = argv[1];
	} else {
		fname = "examples/simple.json";
	}

	struct state s = loader_from_file(fname);

	SDL_Window *win = SDL_CreateWindow("Phy6", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WIN_WIDTH, WIN_HEIGHT, 
			0);

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);

	FC_Font *font = FC_CreateFont();
	FC_LoadFont(font, ren, "fonts/VT323-Regular.ttf", 20, FC_MakeColor(255, 255, 255, 255),
			TTF_STYLE_NORMAL);


	SDL_Event event;

	char quit = 0;

	unsigned long LAST = 0, NOW = SDL_GetPerformanceCounter();
	double dt = 0;

	float scaleline_multip = 1.0f;

	float cam_vel_multip = 5;

	while (!quit) {
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		dt = (double)(NOW - LAST)/(double)SDL_GetPerformanceFrequency();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = 1;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode) {
						case SDL_SCANCODE_DOWN:
							cam.scale /= 1.5;
							break;
						case SDL_SCANCODE_UP:
							cam.scale *= 1.5;
							break;
						case SDL_SCANCODE_W:
							cam.pos.y += 1 * cam_vel_multip;
							break;
						case SDL_SCANCODE_A:
							cam.pos.x += -1 * cam_vel_multip;
							break;
						case SDL_SCANCODE_S:
							cam.pos.y += -1 * cam_vel_multip;
							break;
						case SDL_SCANCODE_D:
							cam.pos.x += 1 * cam_vel_multip;
							break;
					}
					break;
			}
		}

		charges_update(s.c, dt, s.B, s.E);

		SDL_SetRenderDrawColor(ren, 20, 20, 20, 255);
		
		SDL_RenderClear(ren);

		charges_draw(s.c, ren, cam);

		FC_Draw(font, ren, WIN_WIDTH - 100, WIN_HEIGHT - 45, "Scale: 1m");

		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		
		SDL_RenderDrawLine(ren, WIN_WIDTH - 20 - cam.scale, WIN_HEIGHT - 20, WIN_WIDTH - 20, WIN_HEIGHT - 20);

		SDL_RenderPresent(ren);

	}

	FC_FreeFont(font);

	SDL_DestroyWindow(win);

	SDL_DestroyRenderer(ren);

	SDL_Quit();

}
