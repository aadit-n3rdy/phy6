#ifndef PHY6_VIEW_H
#define PHY6_VIEW_H

#include "vec2.h"

struct view {
	float scale;
	vec2_t pos;
	int w;
	int h;
};

inline static vec2_t world_to_screen(vec2_t pos, struct view cam) {
	return (vec2_t){cam.w/2 + pos.x * cam.scale, cam.h/2 - pos.y * cam.scale};
}

inline static vec2_t screen_to_world(vec2_t pos, struct view cam) {
	return (vec2_t){ (float)(pos.x-cam.w/2)/cam.scale,
		(float)(cam.h/2-pos.y)/cam.scale};
}

#endif
