#include <stdlib.h>
#include "Shapes.h"

static void* Rect_ctor(void* _self, va_list* app)
{
	struct Rect* self = super_ctor(Rect, _self, app);

	self -> colour = va_arg(*app, int);

	return self;
}

static void Rect_draw(void* _self, struct Bounds* clip)
{
	struct Rect* self = _self;
	super_draw(Rect, _self, clip);

	struct Bounds* bounds = bounds(self);

	writeFilledRect(bounds->x1, bounds->y1, bounds->x2, bounds->y2, self -> colour);
}

void setRectColour(void* _self, int colour) {
	struct Rect* self = _self;

	self-> colour = colour;
	if(renderer(self)) invalidate(renderer(self), bounds(self));
}

const void* Rect;

void initShapes()
{
	if(!Rect)
		{
			initView();
			Rect = new(ViewClass, "Rect", View,
						 sizeof(struct Rect), ctor, Rect_ctor,
						 draw, Rect_draw,0);
		}
}
