#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "vec2.h"
#include "charge.h"
#include "state.h"
#include "loader.h"

#define WIN_WIDTH	800
#define WIN_HEIGHT	600

int main(int argc, char **argv) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	float SCALE = 10.0f;

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

	SDL_Event event;

	char quit = 0;

	unsigned long LAST = 0, NOW = SDL_GetPerformanceCounter();
	double dt = 0;

	while (!quit) {
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		dt = (double)(NOW - LAST)/(double)SDL_GetPerformanceFrequency();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = 1;
			}
		}

		charges_update(s.c, dt, s.B, s.E);

		SDL_SetRenderDrawColor(ren, 20, 20, 20, 255);
		
		SDL_RenderClear(ren);

		charges_draw(s.c, ren, SCALE);

		SDL_RenderPresent(ren);

	}

	SDL_DestroyWindow(win);

	SDL_DestroyRenderer(ren);

	SDL_Quit();

}
