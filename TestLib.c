#include <stdlib.h>
#include <assert.h>

#include "TestLib.h"
#include "Bounds.h"

void testAll()
{
  testBounds();
}

void testBounds()
{
  struct Bounds bounds1;
  struct Bounds bounds2;
  struct Bounds* result;

  bounds1.x1 = 10;
  bounds1.x2 = 20;
  bounds1.y1 = 10;
  bounds1.y2 = 20;

  bounds2.x1 = 15;
  bounds2.x2 = 25;
  bounds2.y1 = 5;
  bounds2.y2 = 25;

  assert(containsPoint(12, 12, &bounds1));
  assert(!containsPoint(22, 12, &bounds1));
  assert(!containsPoint(2, 12, &bounds1));
  assert(!containsPoint(12, 22, &bounds1));
  assert(!containsPoint(12, 3, &bounds1));

  assert(doIntersect(&bounds1, &bounds2));

  result = intersect(&bounds1, &bounds2);

  assert(result->x1 == 15);
  assert(result->x2 == 20);
  assert(result->y1 == 10);
  assert(result->y2 == 20);

  result = merge(&bounds1, &bounds2);

  assert(result->x1 == 10);
  assert(result->x2 == 25);
  assert(result->y1 == 5);
  assert(result->y2 == 25);

  free(result);
}
