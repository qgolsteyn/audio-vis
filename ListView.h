#ifndef LIST_VIEW_H_
#define LIST_VIEW_H_

#include "View.h"
#include "Bounds.h"

extern const void* ListView;

struct ListView {
	const struct View _;

  int scrollY;
};

void initListView();

#endif
