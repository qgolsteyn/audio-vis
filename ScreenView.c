#include <stdlib.h>
#include "ScreenView.h"

static void* ScreenView_ctor(void* _self, va_list* app)
{
	struct ScreenView* self = super_ctor(ScreenView, _self, app);

	setWidth(self, va_arg(*app, int));
	setHeight(self, va_arg(*app, int));
	self -> backgroundColour = va_arg(*app, int);

	return self;
}

static void ScreenView_draw(void* _self, struct Bounds* clip)
{
	struct ScreenView* self = _self;
	super_draw(ScreenView, _self, clip);
	writeFilledRect(clip->x1, clip->y1, clip->x2, clip->y2, self -> backgroundColour);
}

const void* ScreenView;

void initScreenView()
{
	if(!ScreenView)
	{
		initShapes();
		ScreenView = new(ViewClass, "ScreenView", View,
					 sizeof(struct ScreenView), ctor, ScreenView_ctor,
					 draw, ScreenView_draw, 0);
	}
}
