#ifndef BOUNDS_H_
#define BOUNDS_H_

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

struct Bounds {
	int x1, x2, y1, y2;
};

int containsPoint(int x, int y, struct Bounds* a);
int containsX(int x, struct Bounds* a);
int containsY(int y, struct Bounds* a);
int doIntersect(struct Bounds* a, struct Bounds* b);
struct Bounds* merge(struct Bounds* a, struct Bounds* b);
struct Bounds* intersect(struct Bounds* a, struct Bounds* b);
struct Bounds* cohen_sutherland(struct Bounds* line, struct Bounds* clip);

#endif
