#include "EventHandler.h"

#include <stdlib.h>

#include "View.h"

void addEvent(struct EventHandler* handler, void* event)
{
  struct EventWrapper* wrapper = malloc(sizeof(struct EventWrapper));

  wrapper -> event = event;
  wrapper -> next = 0;

  if(handler -> tail == 0) {
    handler -> head = handler -> tail = wrapper;
  } else {
    handler -> tail -> next = wrapper;
    handler -> tail = wrapper;
  }
}

void consumeEvents(struct EventHandler* handler)
{
  struct EventWrapper* next = handler -> head;
  while(next)
  {
    propagateEvent(handler, next->event);
    struct EventWrapper* temp = next;
    next = next->next;
    free(temp);
  }
  handler->head = 0;
  handler->tail = 0;
}

int propagateChildren(struct EventHandler* handler, struct View* view, void* _event)
{
  struct Event* event = _event;

  struct EventListener* nextListener = view->listenerHead;
  while(nextListener)
  {
    if(event->type == nextListener->type) {
      int result = 0;
      switch (event->type) {
      }
      if(result) return 1;
    }
    nextListener = nextListener->next;
  }

  struct ChildView* prevView = view->viewTail;
  while(prevView)
  {
    struct View* childView = prevView->view;
    if(propagateChildren(handler, childView, event))
      return 1;
    prevView = prevView->prev;
  }

  return 0;
}

void propagateEvent(struct EventHandler* handler, void* event)
{
  propagateChildren(handler, handler->rootView, event);
}
