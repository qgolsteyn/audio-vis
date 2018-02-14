#include <stdlib.h>
#include "View.h"

static void* View_ctor(void* _self, va_list* app)
{
	struct View* self = super_ctor(View, _self, app);

	self -> x = 0;
	self -> y = 0;
	self -> width = 0;
	self -> height = 0;

	self->listenerHead = 0;
	self->listenerTail = 0;

	self->viewHead = 0;
	self->viewTail = 0;

	self -> absBounds = malloc(sizeof(struct Bounds));
	self -> absBounds -> x1 = 0;
	self -> absBounds -> x2 = 0;
	self -> absBounds -> y1 = 0;
	self -> absBounds -> y2 = 0;

	self->renderer = 0;

	self->visible = 1;

	return self;
}

static void View_draw(void* _self, struct Bounds* clip)
{
	(void) _self;
	(void) clip;
}

void draw(void* _self, struct Bounds* clip)
{
	const struct ViewClass* class = classOf(_self);

	class->draw(_self, clip);
}

void super_draw(const void* _class, void* _self, struct Bounds* clip)
{
	const struct ViewClass *superClass = super(_class);

	superClass->draw(_self, clip);
}

static void View_measure(void* _self, struct Bounds* parent)
{
	struct View* self = _self;

	struct Bounds* child = self -> absBounds;
	child -> x1 = parent -> x1 + self -> x;
	child -> x2 = parent -> x1 + self -> x + self -> width;
	child -> y1 = parent -> y1 + self -> y;
	child -> y2 = parent -> y1 + self -> y + self -> height;
	self -> absBounds = child;
}

void measure(void* _self, struct Bounds* parent)
{
	const struct ViewClass* class = classOf(_self);
	class->measure(_self, parent);
}

void super_measure(const void* _class, void* _self, struct Bounds* parent)
{
	const struct ViewClass *superClass = super(_class);
	superClass->measure(_self, parent);
}

void setX(void* _self, int x)
{
	struct View* self = _self;
	self -> x = x;

	struct Bounds newRegion;
	newRegion.x1 = self-> x;
	newRegion.y1 = self -> y;
	newRegion.x2 = self -> x + self -> width;
	newRegion.y2 = self -> y + self -> height;

	struct Bounds* result = merge(self -> absBounds, &newRegion);

	if(self->renderer) invalidate(self->renderer, result);

	free(result);
}

void setY(void* _self, int y)
{
	struct View* self = _self;
	self -> y = y;

	struct Bounds newRegion;
	newRegion.x1 = self-> x;
	newRegion.y1 = self -> y;
	newRegion.x2 = self -> x + self -> width;
	newRegion.y2 = self -> y + self -> height;

	struct Bounds* result = merge(self -> absBounds, &newRegion);

	if(self->renderer) invalidate(self->renderer, result);

	free(result);
}

void setWidth(void* _self, int width)
{
	struct View* self = _self;
	self -> width = width;

	struct Bounds newRegion;
	newRegion.x1 = self-> x;
	newRegion.y1 = self -> y;
	newRegion.x2 = self -> x + self -> width;
	newRegion.y2 = self -> y + self -> height;

	struct Bounds* result = merge(self -> absBounds, &newRegion);

	if(self->renderer) invalidate(self->renderer, result);

	free(result);
}

void setHeight(void* _self, int height)
{
	struct View* self = _self;
	self -> height = height;

	struct Bounds newRegion;
	newRegion.x1 = self-> x;
	newRegion.y1 = self -> y;
	newRegion.x2 = self -> x + self -> width;
	newRegion.y2 = self -> y + self -> height;

	struct Bounds* result = merge(self -> absBounds, &newRegion);

	if(self->renderer) invalidate(self->renderer, result);

	free(result);
}

void setVisible(void* _self, int visible)
{
	struct View* self = _self;
	if(self->visible != visible)
	{
		self->visible = visible;
		invalidate(self->renderer, self->absBounds);
	}
}

void attachView(void* _self, void* view)
{
	struct View* self = _self;

	setRenderer(view, self->renderer);
	measure(self, view);

	struct ChildView* child = malloc(sizeof(struct ChildView));
	child -> next = 0;
	child -> prev = 0;
	child -> view = view;

	if(self -> viewTail == 0) {
		self -> viewHead = self -> viewTail = child;
	} else {
		self -> viewTail -> next = child;
		child -> prev = self -> viewTail;
		self -> viewTail = child;
	}
}

void addEventListener(void* _self, int type, int (*callback)())
{
	struct View* self = _self;

	struct EventListener* child = malloc(sizeof(struct EventListener));
	child -> type = type;
	child -> callback = callback;
	child -> next = 0;

	if(self -> listenerTail == 0) {
		self -> listenerHead = self -> listenerTail = child;
	} else {
		self -> listenerTail -> next = child;
		self -> listenerTail = child;
	}
}

void setRenderer(void* _self, struct Renderer* renderer)
{
	struct View* self = _self;
	self -> renderer = renderer;

	struct ChildView* next = self->viewHead;
	while(next)
	{
		setRenderer(self, renderer);
	}
}

static void* ViewClass_ctor(void* _self, va_list* app) {
	struct ViewClass* self = super_ctor(ViewClass, _self, app);
	typedef void (*voidf) ();
	voidf selector;

#ifdef va_copy
	va_list ap;
	va_copy(ap, *app);
#else
	va_list ap = *app;
#endif

	while((selector = va_arg(ap, voidf)))
	{
		voidf method = va_arg(ap, voidf);

		if(selector == (voidf) draw)
			* (voidf*) & self->draw = method;

		if(selector == (voidf) measure)
							* (voidf*) & self->measure = method;
	}

#ifdef va_copy
	va_end(ap);
#endif

	return self;
}

const void* ViewClass, *View;

void initView()
{
	if(!ViewClass)
		ViewClass = new(Class, "ViewClass", Class, sizeof(struct ViewClass),
						ctor, ViewClass_ctor, 0);
	if(!View)
		View = new(ViewClass, "View", Object, sizeof(struct View),
				   ctor, View_ctor, draw, View_draw, measure, View_measure, 0);
}
