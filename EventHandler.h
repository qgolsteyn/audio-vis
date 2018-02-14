#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

#include "Event.h"

#define TAP_EVENT 1

struct EventWrapper {
  struct EventWrapper* next;
  void* event;
};

struct EventHandler {
  struct View* rootView;

  struct EventWrapper* head;
  struct EventWrapper* tail;
};

void addEvent(struct EventHandler* handler, void* event);
void consumeEvents(struct EventHandler* handler);

void propagateEvent(struct EventHandler* handler, void* event);

#endif
