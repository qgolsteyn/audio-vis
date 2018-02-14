#include "ListView.h"
#include "TouchEventHandler.h"

int onListMove(void* _self, int dx, int dy)
{
  struct ListView* self = _self;
  self->scrollY += dy;
  invalidate(renderer(_self), bounds(_self));
  return 1;
}

static void* ListView_ctor(void* _self, va_list* app)
{
	struct ListView* self = super_ctor(ListView, _self, app);

	self -> scrollY = 0;

  addEventListener(_self, MOVE_EVENT, onListMove);

	return self;
}

static void ListView_draw(void* _self, struct Bounds* clip)
{
	struct ListView* self = _self;
	super_draw(ListView, _self, clip);
}

static void ListView_measure(void* _self, struct Bounds* parent)
{
  struct ListView* self = _self;
  struct View* view = _self;
	super_measure(ListView, _self, parent);

  int count = 0;
  struct ChildView* next = view->viewHead;
  while(next)
  {
    struct View* childView = next->view;

    childView->x = 0;
    childView->y = self->scrollY + count;
    count += childView->y + childView->height;

    next = next->next;
  }
}

const void* ListView;

void initListView()
{
	if(!ListView)
		{
			initView();
			ListView = new(ViewClass, "ListView", View,
						 sizeof(struct ListView), ctor, ListView_ctor,
						 draw, ListView_draw, measure, ListView_measure, 0);
		}
}
