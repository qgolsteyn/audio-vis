#ifndef RENDERER_H_
#define RENDERER_H_

struct Renderer {
  int displayWidth;
  int displayHeight;

  struct View* rootView;
  struct Bounds* damagedRegion;
};

void setRoot(struct Renderer* self, struct View* view);

void render(struct Renderer* self);
void partialRender(struct Renderer* self);

void invalidate(struct Renderer* self, struct Bounds* damagedRegion);

#endif
