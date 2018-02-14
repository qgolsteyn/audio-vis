#ifndef VIEW_H_
#define VIEW_H_

#include "DrawOperations.h"
#include "Object.h"
#include "Bounds.h"
#include "Renderer.h"
#include "Event.h"

extern const void* View;

struct ChildView {
	struct ChildView* next;
	struct ChildView* prev;
	void* view;
};

struct EventListener {
  struct EventListener* next;
  int type;
	int (*callback)();
};

struct View {
	const struct Object _;
	int x, y, width, height;
	struct Bounds* absBounds;

	struct EventListener* listenerHead;
	struct EventListener* listenerTail;

	struct ChildView* viewHead;
	struct ChildView* viewTail;

	struct Renderer* renderer;

	int visible;
};

void draw(void* self, struct Bounds* clip);
void measure(void* self, struct Bounds* parent);

#define	x(p)	(((const struct View *)(p)) -> x)
#define	y(p)	(((const struct View *)(p)) -> y)
#define	width(p)	(((const struct View *)(p)) -> width)
#define	height(p)	(((const struct View *)(p)) -> height)
#define bounds(p)(((const struct View*)(p)) -> absBounds)
#define renderer(p)(((const struct View*)(p)) -> renderer)

void attachView(void* self, void* view);
void detachView(void* self, void* view);

void addEventListener(void* self, int type, int (*callback)());
void removeEventListener(void* self, int type);

void setRenderer(void* self, struct Renderer* renderer);

void setX(void* self, int x);
void setY(void* self, int y);
void setWidth(void* self, int width);
void setHeight(void* self, int height);
void setVisible(void* self, int visible);

extern const void* ViewClass;

void super_draw(const void* class, void* self, struct Bounds* clip);
void super_measure(const void* class, void* self, struct Bounds* parent);

struct ViewClass {
	const struct Class _;
	void (*draw) (void* self, struct Bounds* clip);
	void (*measure) (void* self, struct Bounds* parent);
};

void initView(void);

#endif /* VIEW_H_ */
