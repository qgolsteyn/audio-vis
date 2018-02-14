#ifndef EVENT_H_
#define EVENT_H_

#include "Object.h"

typedef int EventType;

extern const void* Event;

struct Event {
  const struct Object _;

  EventType type;
};

extern const void* EventClass;

struct EventClass {
  const struct Class _;
};

void initEvent(void);

#endif
