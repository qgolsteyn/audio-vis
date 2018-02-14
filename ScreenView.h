#ifndef SCREENVIEW_H_
#define SCREENVIEW_H_

#include "Shapes.h"

extern const void* ScreenView;

struct ScreenView {
	const struct View _;

	int backgroundColour;
};

void initScreenView();

#endif
