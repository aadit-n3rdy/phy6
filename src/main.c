#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "vec2.h"
#include "charge.h"

#define WIN_WIDTH	800
#define WIN_HEIGHT	600

//const float K = 9e9;

float B = 5;
vec2_t E = {0, 0};

float sigmoid(float q) {
	return 1.0f/(1.0f + expf(-q));
}

void draw_circle(SDL_Renderer *ren, int x0, int y0, int radius)
{
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
        SDL_RenderDrawPoint(ren, x0 + x, y0 + y);
        SDL_RenderDrawPoint(ren, x0 + y, y0 + x);
        SDL_RenderDrawPoint(ren, x0 - y, y0 + x);
        SDL_RenderDrawPoint(ren, x0 - x, y0 + y);
        SDL_RenderDrawPoint(ren, x0 - x, y0 - y);
        SDL_RenderDrawPoint(ren, x0 - y, y0 - x);
        SDL_RenderDrawPoint(ren, x0 + y, y0 - x); 
	SDL_RenderDrawPoint(ren, x0 + x, y0 - y);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

struct Charge {
	vec2_t pos;
	vec2_t vel;
	vec2_t f;
	float q;
	float m;
};


void update_charges(struct Charge *c, int n, float dt) {

	for (int i = 0; i < n; i++) {
		c[i].f = vec2_multip(E, c[i].q);
	}

	vec2_t f;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			vec2_t r = vec2_add(c[j].pos, vec2_multip(c[i].pos, -1));
			float mag = vec2_norm(r);
			f = vec2_multip(r, c[i].q * c[j].q * (float)K / (mag * mag * mag));
			c[j].f = vec2_add(c[j].f, f);
			c[i].f = vec2_add(c[i].f, vec2_multip(f, -1.0f));
		}
	}

	for (int i = 0; i < n; i++) {
		c[i].vel = vec2_add(c[i].vel, vec2_multip(c[i].f, dt/c[i].m));
		c[i].pos = vec2_add(vec2_multip(c[i].vel, dt), c[i].pos);
	}
}

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
		{(vec2_t){0, 0},   (vec2_t){0, 0},  (vec2_t){0, 0}, 1e-4 , 10.0f, 0},
		{(vec2_t){0, 10},  (vec2_t){0, 0},  (vec2_t){0, 0}, 10e-4, 10.0f, 0},
		{(vec2_t){0, -10}, (vec2_t){0, 0},  (vec2_t){0, 0}, 1e-4, 10.0f, 0}
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

//		for (int i = 0; i < 3; i++) {
//			unsigned int red = 255.0f * sigmoid(charges[i].q * 10000);
//			SDL_SetRenderDrawColor(ren, red, 128, -red, 255);
//			draw_circle(ren, 400 + charges[i].pos.x * SCALE, 300 + charges[i].pos.y * SCALE, abs(charges[i].m));
//		}

		SDL_RenderPresent(ren);

	}

	SDL_DestroyWindow(win);

	SDL_DestroyRenderer(ren);

	SDL_Quit();

}
