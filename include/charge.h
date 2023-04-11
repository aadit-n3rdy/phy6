#ifndef PHY6_CHARGE_H
#define PHY6_CHARGE_H

#include "vec2.h"
#include "view.h"

#include <SDL2/SDL.h>

#define K (9e9)

struct charge {
	vec2_t pos;
	vec2_t vel;
	vec2_t f;
	float q;
	float m;

	struct charge *next;
};

struct env {
	vec2_t E;
	float B;
};

int charges_update(struct charge *c, const float dt, const float B, const vec2_t E);

struct charge* charges_insert(struct charge *clist, struct charge *c);

int charges_draw(struct charge *c, SDL_Renderer *ren, struct view cam);

void draw_circle(SDL_Renderer *ren, int x0, int y0, int radius);

#endif
