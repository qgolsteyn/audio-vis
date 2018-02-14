#include <stdlib.h>
#include "ProgressBar.h"
#include "TouchEventHandler.h"

int onProgressBarDown(void* _self, int x, int y)
{
  struct ProgressBar* self = _self;
  if(x < 0) self -> percentage = 0;
  else if(x > width(self)) self->percentage = 1;
  else self->percentage = ((double) x) / width(self);
  invalidate(renderer(self), bounds(self));
  return 1;
}

int onProgressBarMove(void* _self, int x, int y, int dx, int dy)
{
  return onProgressBarDown(_self, x, y);
}

static void* ProgressBar_ctor(void* _self, va_list* app)
{
	struct ProgressBar* self = super_ctor(ProgressBar, _self, app);

	self -> colour = va_arg(*app, int);

  self -> percentage = 0;

  addEventListener(self, DOWN_EVENT, onProgressBarDown);
  addEventListener(self, MOVE_EVENT, onProgressBarMove);

	return self;
}

static void ProgressBar_draw(void* _self, struct Bounds* clip)
{
	struct ProgressBar* self = _self;
	super_draw(ProgressBar, _self, clip);

	struct Bounds* bounds = bounds(self);

  writeFilledRect(bounds->x1, bounds->y1, bounds->x2, bounds->y2, BLACK);
	writeFilledRect(bounds->x1, bounds->y1, bounds->x1 + width(self)*self->percentage, bounds->y2, self -> colour);
}

const void* ProgressBar;

void initProgressBar()
{
	if(!ProgressBar)
		{
			initView();
			ProgressBar = new(ViewClass, "ProgressBar", View,
						 sizeof(struct ProgressBar), ctor, ProgressBar_ctor,
						 draw, ProgressBar_draw,0);
		}
}
