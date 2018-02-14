#ifndef SHAPES_H_
#define SHAPES_H_

#include "View.h"

extern const void* Rect;

struct Rect {
	const struct View _;

	int colour;
};

void setRectColour(void* self, int colour);

void initShapes();

#endif
