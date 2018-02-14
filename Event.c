#include "Event.h"

static void* Event_ctor(void* _self, va_list* app)
{
  struct Event* self = super_ctor(Event, _self, app);
  self -> type = va_arg(*app, int);

  return self;
}

static void* EventClass_ctor(void* _self, va_list* app)
{
  struct EventClass* self = super_ctor(EventClass, _self, app);

  return self;
}

const void* EventClass, *Event;

void initEvent()
{
  if(!EventClass)
  {
    EventClass = new(Class, "EventClass", Class, sizeof(struct EventClass), ctor, EventClass_ctor, 0);
  }
  if(!Event)
  {
    Event = new(EventClass, "Event", Object, sizeof(struct Event), ctor, Event_ctor, 0);
  }
}
