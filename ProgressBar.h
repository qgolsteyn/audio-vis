#ifndef PROGRESSBAR_H_
#define PROGRESSBAR_H_

#include "View.h"

extern const void* ProgressBar;

struct ProgressBar {
	const struct View _;

	int colour;

  double percentage;
};

void initProgressBar();

#endif
