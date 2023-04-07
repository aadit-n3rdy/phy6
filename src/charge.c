#include "charge.h"

#include "vec2.h"

static float sigmoid(float q) {
	return 1.0f/(1.0f + expf(-q));
}

static void draw_circle(SDL_Renderer *ren, int x0, int y0, int radius)
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

int charges_update(struct charge *root, const float dt, const float B, const vec2_t E) {
	struct charge *c, *d;
	vec2_t f;
	float mag;

	for (c = root; c != NULL; c = c->next) {
		c->f = vec2_add(vec2_multip(E, c->q), vec2_cross(c->vel, B));
	}

	for (c = root; c != NULL; c = c->next) {
		for (d = c->next; d != NULL; d = d->next) {
			vec2_t r = vec2_add(d->pos, vec2_multip(c->pos, -1));
			mag = vec2_norm(r);
			f = vec2_multip(r, c->q * d->q * K / (mag * mag * mag));
			d->f = vec2_add(d->f, f);
			c->f = vec2_add(c->f, vec2_multip(f, -1.0f));
		}
	}

	for (c = root; c != NULL; c = c->next) {
		c->vel = vec2_add(c->vel, vec2_multip(c->f, dt/c->m));
		c->pos = vec2_add(vec2_multip(c->vel, dt), c->pos);
	}

}

struct charge* charges_insert(struct charge *clist, struct charge *c) {
	c->next = clist;
	return c;
}

int charges_draw(struct charge *c, SDL_Renderer *ren, float scale) {
	unsigned int red;
	int w, h;
	SDL_GetRendererOutputSize(ren, &w, &h);
	w /= 2;
	h /= 2;
	while (c != NULL) {
		red = 255.0f * sigmoid(c->q * 10000);
		SDL_SetRenderDrawColor(ren, red, 128, 255 - red, 255);
		draw_circle(ren, w + c->pos.x * scale, h - c->pos.y * scale, abs(c->m));
		c = c->next;
	}
}
