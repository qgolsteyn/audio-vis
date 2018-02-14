#include "TouchEventHandler.h"

#include <stdlib.h>

#include "View.h"
#include "DE1_SOC_touchscreen.h"
#include "Bounds.h"

void removeRestOfPath(struct TouchEventPath* next)
{
  while(next) {
    struct View* view = next->view;
    struct EventListener* nextListener = view->listenerHead;
    while(nextListener)
    {
      if(UP_EVENT == nextListener->type) {
        nextListener->callback(view);
      }
      nextListener = nextListener->next;
    }

    struct TouchEventPath* temp = next;
    next = next->next;
    free(temp);
  }
}

void handleDown(struct TouchEventHandler* handler)
{
  struct Point point = DE1_getLastTouchLocation();
  printf("%d,%d\n", point.x, point.y);
  generateTouchList(handler, point.x, point.y);
  propagateTouchEvent(handler, DOWN_EVENT);
  handler->pastPressed = 1;
  handler->x = point.x;
  handler->y = point.y;
}

void handleMove(struct TouchEventHandler* handler)
{
  struct Point point = DE1_getLastTouchLocation();
  printf("%d,%d\n", point.x, point.y);
  handler->dx = point.x - handler->x;
  handler->dy = point.y - handler->y;
  if(handler->moving) {
    handler->x = point.x;
    handler->y = point.y;
    propagateTouchEvent(handler, MOVE_EVENT);
  } else {
    if(abs(handler->dx) > 12 || abs(handler->dy) > 12) {
      handler->dx = 0;
      handler->dy = 0;
      handler->moving = 1;
      handler->x = point.x;
      handler->y = point.y;
      propagateTouchEvent(handler, MOVE_EVENT);
    } else {
      handleDown(handler);
    }
  }
}

void handleUp(struct TouchEventHandler* handler)
{
  struct TouchEventPath* next = handler->head;
  while(next) {
    struct View* view = next->view;
    int withinBounds = containsPoint(handler->x, handler->y, view->absBounds);
    struct EventListener* nextListener = view->listenerHead;
    while(nextListener)
    {
      if(UP_EVENT == nextListener->type) {
        nextListener->callback(view, handler->x, handler->y);
      } else if(withinBounds && CLICK_EVENT == nextListener->type) {
        nextListener->callback(view);
      }
      nextListener = nextListener->next;
    }

    struct TouchEventPath* temp = next;
    next = next->next;
    free(temp);
  }

  handler->head = handler->tail = 0;
  handler->pastPressed = 0;
  handler->moving = 0;
}

void handleTouch(struct TouchEventHandler* handler)
{
  printf("%d\n", DE1_isScreenTouched());
  if(DE1_isScreenTouched()) {
    if(!handler->pastPressed) {
      printf("TouchDown\n");
      handleDown(handler);
    } else {\
      printf("TouchMove\n");
      handleMove(handler);
    }
  } else if(handler->pastPressed) {
	printf("TouchUp\n");
    handleUp(handler);
  }
}

void propagateTouchEvent(struct TouchEventHandler* handler, int type)
{
  struct TouchEventPath* next = handler->head;
  while(next) {
    struct View* view = next->view;
    struct EventListener* nextListener = view->listenerHead;
    while(nextListener)
    {
      if(type == nextListener->type) {
        int result = 0;
        switch (type) {
          case DOWN_EVENT:;
          result = nextListener->callback(view, handler->x - view->absBounds->x1, handler->y - view->absBounds->y1);
          break;
          case UP_EVENT:;
          result = nextListener->callback(view, handler->x - view->absBounds->x1, handler->y - view->absBounds->y1);
          break;
          case MOVE_EVENT:;
          result = nextListener->callback(view, handler->x - view->absBounds->x1, handler->y - view->absBounds->y1, handler->dx, handler->dy);
          break;
          case CLICK_EVENT:;
          result = nextListener->callback(view);
          break;
        }
        if(result){
          removeRestOfPath(next->next);
          next->next = 0;
        }
      }
      nextListener = nextListener->next;
    }

    next = next->next;
  }
}

void generateTouchListChildren(struct TouchEventHandler* handler, void* _view, int x, int y)
{
  struct View* view = _view;
  if(containsPoint(x, y, view->absBounds)) {
    struct TouchEventPath* path = malloc(sizeof(struct TouchEventPath));
    path->view = _view;
    path->next = 0;
    if(handler->tail) {
      handler->tail->next = path;
      handler->tail = path;
    } else {
      handler->head = handler->tail = path;
    }

    struct ChildView* prevView = view->viewTail;
    while(prevView)
    {
      struct View* childView = prevView->view;
      generateTouchListChildren(handler, childView, x, y);
      prevView = prevView->prev;
    }
  }
}

void generateTouchList(struct TouchEventHandler* handler, int x, int y)
{
  generateTouchListChildren(handler, handler->rootView, x, y);
}
