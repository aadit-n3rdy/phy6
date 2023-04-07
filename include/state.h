#ifndef PHY6_STATE_H
#define PHY6_STATE_H

#include "charge.h"
#include "vec2.h"

struct state {
	struct charge *c;
	vec2_t E;
	float B;
};


#endif
