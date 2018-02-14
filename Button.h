#ifndef BUTTON_H_
#define BUTTON_H_

#include "View.h"

extern const void* Button;

struct Button {
	const struct View _;

	int colour;
  int focusColour;

  int focused;
};

void initButton();

#endif
