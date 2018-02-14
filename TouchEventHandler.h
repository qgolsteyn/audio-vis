#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

#include "Event.h"

#define DOWN_EVENT 1
#define UP_EVENT 2
#define MOVE_EVENT 3
#define CLICK_EVENT 4

struct TouchEventPath {
  struct TouchEventPath* next;
  void* view;
};

struct TouchEventHandler {
  struct View* rootView;

  struct TouchEventPath* head;
  struct TouchEventPath* tail;

  int pastPressed;
  int moving;

  int x, y, dx, dy;
};


void handleTouch(struct TouchEventHandler* handler);
void propagateTouchEvent(struct TouchEventHandler* handler, int type);
void generateTouchList(struct TouchEventHandler* handler, int x, int y);

#endif
