#include "Renderer.h"

#include <stdlib.h>

#include "View.h"
#include "Bounds.h"
#include "DrawOperations.h"

void setRoot(struct Renderer* self, struct View* view)
{
  self->rootView = view;

  struct Bounds clip;
  clip.x1 = 30;
  clip.y1 = 0;
  clip.x2 = self -> displayWidth - 1;
  clip.y2 = self -> displayHeight - 1;

  measure(view, &clip);
}

void renderChildren(struct Renderer* self, struct View* view, struct Bounds* clip)
{
  setClippingBounds(clip);

  draw(view, clip);

  struct ChildView* next = view->viewHead;
  while(next)
  {
    struct View* childView = next->view;
    measure(childView, view -> absBounds);

    if(childView->visible && doIntersect(childView -> absBounds, clip))
    {
      struct Bounds* childClip = intersect(childView -> absBounds, clip);
      renderChildren(self, childView, childClip);
      free(childClip);
    }

    next = next->next;
  }
}

void render(struct Renderer* self)
{
  struct Bounds clip;
  clip.x1 = 30;
  clip.y1 = 0;
  clip.x2 = self -> displayWidth - 1;
  clip.y2 = self -> displayHeight - 1;

  measure(self -> rootView, &clip);

  renderChildren(self, self -> rootView, &clip);
}
void partialRender(struct Renderer* self)
{
  if(self -> damagedRegion) {
    struct Bounds clip;
    clip.x1 = 30;
    clip.y1 = 0;
    clip.x2 = self -> displayWidth - 1;
    clip.y2 = self -> displayHeight - 1;

    measure(self -> rootView, &clip);

    renderChildren(self, self -> rootView, self -> damagedRegion);

    self -> damagedRegion = 0;
  }
}

void invalidate(struct Renderer* self, struct Bounds* damagedRegion)
{
  if(self->damagedRegion)
  {
    struct Bounds* temp = self->damagedRegion;
    self -> damagedRegion = merge(damagedRegion, self -> damagedRegion);
    free(temp);
  } else {
    self -> damagedRegion = malloc(sizeof(struct Bounds));
    self -> damagedRegion -> x1 = damagedRegion -> x1;
    self -> damagedRegion -> y1 = damagedRegion -> y1;
    self -> damagedRegion -> x2 = damagedRegion -> x2;
    self -> damagedRegion -> y2 = damagedRegion -> y2;
  }
}
