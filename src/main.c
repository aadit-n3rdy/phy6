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

void state_free(struct state s) {
	struct charge *next;
	struct charge *cur;
	cur = s.c;
	while (cur != NULL) {
		next = cur->next;
		free(cur);
		cur = next;
	}
}

vec2_t calc_E(struct state s, vec2_t pos) {
	vec2_t E = s.E;
	vec2_t r;
	struct charge *i;
	for (i = s.c; i != NULL; i = i->next) {
		r = vec2_add(pos, vec2_multip(i->pos, -1));
		E = vec2_add(vec2_multip(vec2_normalised(r), K * i->q/powf(vec2_norm(r), 2)), E);
	}
	return E;
}

void draw_field(SDL_Renderer *ren, struct state s, char *e_text, vec2_t pos, struct view cam) {
	vec2_t E = calc_E(s, pos);
	float mag = vec2_norm(E);
	sprintf(e_text, "%e", mag);
	vec2_t offset = vec2_multip(E, 0.1f/mag);
	vec2_t p1 = world_to_screen(pos, cam);
	vec2_t p2 = world_to_screen(vec2_add(pos, vec2_multip(offset, cam.scale)), cam);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderDrawLine(ren, p1.x, p1.y, p2.x, p2.y);
	draw_circle(ren, p2.x, p2.y, 3);
	sprintf(e_text, "%e", mag);
}

void update_info_text(struct state s, char *info_text, int mX, int mY, struct view cam) {
	int w = WIN_WIDTH/2;
	int h = WIN_HEIGHT/2;
	struct charge *i;
	int qx, qy;
	char done = 0;

	for (i = s.c; i != NULL; i = i->next) {
		qx = w + i->pos.x * cam.scale;
		qy = h - i->pos.y * cam.scale;
		if (abs(mX - qx) <= i->m && abs(mY - qy) <= i->m) {
			done = 1;
			break;
		}
	}
	if (done) {
		sprintf(info_text, "x: (%e %e)\nQ: %e\nm: %e\nv: (%e %e)\na: (%e %e)\n",
				i->pos.x,
				i->pos.y,
				i->q,
				i->m,
				i->vel.x,
				i->vel.y,
				i->f.x / i->m,
				i->f.y / i->m);
	} else {
		vec2_t pos = (vec2_t){ (float)(mX-w)/cam.scale,
			(float)(h-mY)/cam.scale};
		vec2_t E = s.E;
		vec2_t r;
		for (i = s.c; i != NULL; i = i->next) {
			r = vec2_add(pos, vec2_multip(i->pos, -1));
			E = vec2_add(vec2_multip(vec2_normalised(r), K * i->q/powf(vec2_norm(r), 2)), E);
		}
		sprintf(info_text, "x: (%e %e)\nE: (%e %e)\n", pos.x, pos.y, E.x, E.y);
	}
}

int main(int argc, char **argv) {

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	struct view cam;
	cam.scale = 10;
	cam.pos = (vec2_t){0, 0};
	cam.w = WIN_WIDTH;
	cam.h = WIN_HEIGHT;

	char fname[128];

	vec2_t monitor_pos = (vec2_t){0, 0};

	strcpy(fname, (argc > 1) ? argv[1] : "examples/simple.json");

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
	float timescale = 1.0f;

	char info_text[128] = "Click on a point to view the \nelectric field at the point";
	char e_text[128] = "";

	vec2_t click = {0, 0};
	vec2_t clicktext = vec2_add(world_to_screen(click, cam), (vec2_t){10, 10});

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
						case SDL_SCANCODE_R:
							printf("Reloading file %s\n", fname);
							state_free(s);
							s = loader_from_file(fname);
							cam.scale = 10;
							cam.pos = (vec2_t){0, 0};
							break;
						case SDL_SCANCODE_F:
							printf("Enter the file to load from: \n");
							scanf("%s", fname);
							state_free(s);
							s = loader_from_file(fname);
							cam.scale = 10;
							cam.pos = (vec2_t){0, 0};
							printf("Press R to begin\n");
							break;
						case SDL_SCANCODE_SPACE:
							timescale = (timescale > 0) ? 0 : 1;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					switch (event.button.button) {
						case SDL_BUTTON_LEFT:
							update_info_text(s, info_text, event.button.x, event.button.y, cam);
							click = screen_to_world(
									(vec2_t){event.button.x, event.button.y},
									cam);
							clicktext = (vec2_t) {event.button.x + 10,
								event.button.y + 10};
							break;

					}
					break;
			}
		}

		charges_update(s.c, timescale * dt, s.B, s.E);

		SDL_SetRenderDrawColor(ren, 20, 20, 20, 255);
		
		SDL_RenderClear(ren);

		charges_draw(s.c, ren, cam);

		FC_Draw(font, ren, WIN_WIDTH - 100, WIN_HEIGHT - 45, "Scale: 1m");

		FC_Draw(font, ren, 10, 10, info_text);

		draw_field(ren, s, e_text, click, cam);
		FC_Draw(font, ren, clicktext.x, clicktext.y,
				e_text);

		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		
		SDL_RenderDrawLine(ren, WIN_WIDTH - 20 - cam.scale, WIN_HEIGHT - 20, WIN_WIDTH - 20, WIN_HEIGHT - 20);

		SDL_RenderPresent(ren);

	}

	FC_FreeFont(font);

	SDL_DestroyWindow(win);

	SDL_DestroyRenderer(ren);

	SDL_Quit();

}
