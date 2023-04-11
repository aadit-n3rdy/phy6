#ifndef PHY6_VEC2_H
#define PHY6_VEC2_H

#include <math.h>

struct vec2 {
	float x;
	float y;
};

typedef struct vec2 vec2_t;

inline static vec2_t vec2_add(vec2_t a, vec2_t b) {
	return (vec2_t) {a.x + b.x, a.y + b.y};
}

inline static float vec2_norm(vec2_t a) {
	return powf(a.x * a.x + a.y * a.y, 0.5f);
}

inline static vec2_t vec2_multip(vec2_t a, float b) {
	return (vec2_t) {a.x * b, a.y * b};
}

inline static vec2_t vec2_cross(vec2_t a, float z) {
	return (vec2_t) {a.y * z, -a.x * z};
}

inline static vec2_t vec2_normalised(vec2_t a) {
	return vec2_multip(a, 1.0f/vec2_norm(a));
}

#endif
