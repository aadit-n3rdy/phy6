#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "vec2.h"
#include "charge.h"

#define WIN_WIDTH	800
#define WIN_HEIGHT	600

vec2_t E = {0, 0};
float B = 5;

int main() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	float SCALE = 10.0f;

	SDL_Window *win = SDL_CreateWindow("Phy6", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WIN_WIDTH, WIN_HEIGHT, 
			0);

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);

	SDL_Event event;

	char quit = 0;

	struct charge charges[3] = {
		{(vec2_t){0, 0},   (vec2_t){0, 0},  (vec2_t){0, 0}, -1e-4 , 10.0f, 0},
		{(vec2_t){0, 10},  (vec2_t){0, 0},  (vec2_t){0, 0}, 10e-4, 10.0f, 0},
		{(vec2_t){0, -10}, (vec2_t){0, 0},  (vec2_t){0, 0}, -1e-4, 10.0f, 0}
	};

	struct charge *l = NULL;

	for (int i= 0; i < 3; i++) {
		l = charges_insert(l, &charges[i]);
	}

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

		charges_update(l, dt, B, E);

		SDL_SetRenderDrawColor(ren, 20, 20, 20, 255);
		
		SDL_RenderClear(ren);

		charges_draw(l, ren, SCALE);

		SDL_RenderPresent(ren);

	}

	SDL_DestroyWindow(win);

	SDL_DestroyRenderer(ren);

	SDL_Quit();

}
