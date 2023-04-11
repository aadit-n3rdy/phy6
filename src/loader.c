#include "loader.h"

#include "charge.h"
#include "state.h"

#include "cJSON.h"

#include <stdio.h>
#include <stdlib.h>

struct state loader_from_file(const char *fname) {

	struct state ret;
	ret.B = 0;
	ret.E = (vec2_t){0, 0};
	ret.c = NULL;

	FILE *fp = fopen(fname, "r");
	
	if (!fp) {
		printf("ERROR: Could not open file for reading: %s\n", fname);
		goto end;
	}

	fseek(fp, 0, SEEK_END);
	size_t len = ftell(fp);
	rewind(fp);

	char *buf = malloc(len + 1);
	fread(buf, 1, len + 1, fp);
	fclose(fp);
	buf[len] = '\0';

	printf("Read %d bytes from %s\n", len, fname);

	cJSON *cj = cJSON_Parse(buf);

	cJSON *charges = cJSON_GetObjectItem(cj, "charges");
	if (!cJSON_IsArray(charges)) {
		printf("ERROR: charges is not an array\n");
		goto end;
	}
	printf("Found charges array...\n");

	struct charge* c;
	cJSON *pos, *vel, *q, *m, *cjc;
	cJSON_ArrayForEach(cjc, charges) {
		if (!cJSON_IsObject(cjc)) {
			printf("ERROR: charge is not an object\n");
			goto end;
		}
		c = malloc(sizeof(struct charge));
		pos = cJSON_GetObjectItem(cjc, "pos");
		vel = cJSON_GetObjectItem(cjc, "vel");
		q = cJSON_GetObjectItem(cjc, "charge");
		m = cJSON_GetObjectItem(cjc, "mass");

		c->pos.x = cJSON_GetArrayItem(pos, 0)->valuedouble;
		c->pos.y = cJSON_GetArrayItem(pos, 1)->valuedouble;

		c->vel.x = cJSON_GetArrayItem(vel, 0)->valuedouble;
		c->vel.y = cJSON_GetArrayItem(vel, 1)->valuedouble;

		c->q = q->valuedouble;

		c->m = m->valuedouble;

		ret.c = charges_insert(ret.c, c);

		printf("Charge: \n");
		printf("pos: [%f %f]\nvel: [%f %f]\nq: %f\nm: %f\n\n",
				c->pos.x, c->pos.y, c->vel.x, c->vel.y, c->q, c->m);
	}

	cJSON *b = cJSON_GetObjectItem(cj, "B");
	if (cJSON_IsNumber(b)) {
		ret.B = b->valuedouble;
	} else {
		ret.B = 0;
	}

	cJSON *e = cJSON_GetObjectItem(cj, "E");
	if (cJSON_IsArray(e)) {
		ret.E.x = cJSON_GetArrayItem(e, 0)->valuedouble;
		ret.E.y = cJSON_GetArrayItem(e, 1)->valuedouble;
	}

	printf("B: %f\nE: [%f %f]\n", ret.B, ret.E.x, ret.E.y);
end:
	printf("\n");
	cJSON_Delete(cj);
	free(buf);
	printf("Finished loading file %s\n", fname);
	return ret;
} 
