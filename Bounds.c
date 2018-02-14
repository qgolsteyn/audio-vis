#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Bounds.h"

typedef int OutCode;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

int containsPoint(int x, int y, struct Bounds* a)
{
	return containsX(x, a) && containsY(y, a);
}

int containsY(int y, struct Bounds* a)
{
	if(y < a -> y1 || y > a -> y2)
		return 0;

	return 1;
}

int containsX(int x, struct Bounds* a)
{
	if(x < a -> x1 || x > a -> x2)
		return 0;

	return 1;
}

int doIntersect(struct Bounds* a, struct Bounds* b)
{
	return (a->x1 < b->x2 && a->x2 > b->x1 &&
    a->y1 < b->y2 && a->y2 > b->y1);
}

struct Bounds* merge(struct Bounds* a, struct Bounds* b)
{
	assert(a->x1 <= a->x2);
	assert(a->y1 <= a->y2);
	assert(b->x1 <= b->x2);
	assert(b->y1 <= b->y2);

	struct Bounds* result = malloc(sizeof(struct Bounds));
	result->x1 = MIN(a->x1, b->x1);
	result->y1 = MIN(a->y1, b->y1);
	result->x2 = MAX(a->x2, b->x2);
	result->y2 = MAX(a->y2, b->y2);

	return result;
}

struct Bounds* intersect(struct Bounds* a, struct Bounds* b)
{
	assert(a->x1 <= a->x2);
	assert(a->y1 <= a->y2);
	assert(b->x1 <= b->x2);
	assert(b->y1 <= b->y2);

	struct Bounds* result = malloc(sizeof(struct Bounds));
	result->x1 = MAX(a->x1, b->x1);
	result->y1 = MAX(a->y1, b->y1);
	result->x2 = MIN(a->x2, b->x2);
	result->y2 = MIN(a->y2, b->y2);

	return result;
}

int computeOutCode(double x, double y, struct Bounds* clip)
{
	int xmin = clip -> x1;
	int xmax = clip -> x2;
	int ymin = clip -> y1;
	int ymax = clip -> y2;

	OutCode code;

	code = INSIDE;          // initialised as being inside of [[clip window]]

	if (x < xmin)           // to the left of clip window
		code |= LEFT;
	else if (x > xmax)      // to the right of clip window
		code |= RIGHT;
	if (y < ymin)           // below the clip window
		code |= BOTTOM;
	else if (y > ymax)      // above the clip window
		code |= TOP;

	return code;
}

struct Bounds* cohen_sutherland(struct Bounds* line, struct Bounds* clip)
{
	double x0 = line -> x1;
	double y0 = line -> y1;
	double x1 = line -> x2;
	double y1 = line -> y2;

	int xmin = clip -> x1;
	int xmax = clip -> x2;
	int ymin = clip -> y1;
	int ymax = clip -> y2;

	// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
	OutCode outcode0 = computeOutCode(x0, y0, clip);
	OutCode outcode1 = computeOutCode(x1, y1, clip);
	int accept = 0;

	while (1) {
		if (!(outcode0 | outcode1)) {
			// bitwise OR is 0: both points inside window; trivially accept and exit loop
			accept = 1;
			break;
		} else if (outcode0 & outcode1) {
			// bitwise AND is not 0: both points share an outside zone (LEFT, RIGHT, TOP,
			// or BOTTOM), so both must be outside window; exit loop (accept is false)
			break;
		} else {
			// failed both tests, so calculate the line segment to clip
			// from an outside point to an intersection with clip edge
			double x, y;

			// At least one endpoint is outside the clip rectangle; pick it.
			OutCode outcodeOut = outcode0 ? outcode0 : outcode1;

			// Now find the intersection point;
			// use formulas:
			//   slope = (y1 - y0) / (x1 - x0)
			//   x = x0 + (1 / slope) * (ym - y0), where ym is ymin or ymax
			//   y = y0 + slope * (xm - x0), where xm is xmin or xmax
			// No need to worry about divide-by-zero because, in each case, the
			// outcode bit being tested guarantees the denominator is non-zero
			if (outcodeOut & TOP) {           // point is above the clip window
				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			} else if (outcodeOut & BOTTOM) { // point is below the clip window
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				y = ymin;
			} else if (outcodeOut & RIGHT) {  // point is to the right of clip window
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			} else if (outcodeOut & LEFT) {   // point is to the left of clip window
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}

			// Now we move outside point to intersection point to clip
			// and get ready for next pass.
			if (outcodeOut == outcode0) {
				x0 = x;
				y0 = y;
				outcode0 = computeOutCode(x0, y0, clip);
			} else {
				x1 = x;
				y1 = y;
				outcode1 = computeOutCode(x1, y1, clip);
			}
		}
	}

	if(accept) {
		struct Bounds* result = malloc(sizeof(struct Bounds));
		result -> x1 = x0;
		result -> x2 = x1;
		result -> y1 = y0;
		result -> y2 = y1;

		return result;
	} else {
		return 0;
	}
}
