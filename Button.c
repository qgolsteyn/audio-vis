#include <stdlib.h>
#include "Button.h"
#include "TouchEventHandler.h"

int onButtonDown(void* _self, int x, int y)
{
  (void) x;
  (void) y;
  struct Button* self = _self;
  self -> focused = 1;
  invalidate(renderer(self), bounds(self));
  return 1;
}

int onButtonUp(void* _self, int x, int y)
{
  (void) x;
  (void) y;
  struct Button* self = _self;
  self -> focused = 0;
  invalidate(renderer(self), bounds(self));
  return 1;
}

static void* Button_ctor(void* _self, va_list* app)
{
	struct Button* self = super_ctor(Button, _self, app);

	self -> colour = va_arg(*app, int);
  self -> focusColour = va_arg(*app, int);

  self -> focused = 0;

  addEventListener(self, DOWN_EVENT, onButtonDown);
  addEventListener(self, UP_EVENT, onButtonUp);

	return self;
}

static void Button_draw(void* _self, struct Bounds* clip)
{
	struct Button* self = _self;
	super_draw(Button, _self, clip);

	struct Bounds* bounds = bounds(self);

	writeFilledRect(bounds->x1, bounds->y1, bounds->x2, bounds->y2, self -> focused ? self -> focusColour : self -> colour);
}

const void* Button;

void initButton()
{
	if(!Button)
		{
			initView();
			Button = new(ViewClass, "Button", View,
						 sizeof(struct Button), ctor, Button_ctor,
						 draw, Button_draw,0);
		}
}
