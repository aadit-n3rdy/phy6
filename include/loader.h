#ifndef PHY6_LOADER_H
#define PHY6_LOADER_H

#include "charge.h"
#include "state.h"

struct state loader_from_file(const char *fname);

int loader_free(struct charge* c);

#endif
