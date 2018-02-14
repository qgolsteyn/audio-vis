#ifndef DRAWOPERATIONS_H_
#define DRAWOPERATIONS_H_

#include "Bounds.h"

//Predefined Colour Values
//Use the symbolic constants below as the values to write to the Colour Register
//When you ask the graphics chip to draw something. These values are also returned
//By the read pixel command

// the header file "Colours.h" contains symbolic names for all 256 colours e.g. RED
// while the source file ColourPaletteData.c contains the 24 bit RGB data
// that is pre-programmed into each of the 256 palettes

#define	BLACK		0
#define	WHITE		1
#define	RED			2
#define	LIME		3
#define	BLUE		4
#define	YELLOW		5
#define	CYAN		6
#define	MAGENTA		7

void setClippingBounds(struct Bounds* clip);

void writeAPixel (int x, int y, int color);
int readAPixel (int x, int y);

void programPalette(int PaletteNumber, int RGB);

void writeHline (int y, int x1, int x2, int color);
void writeVline (int x, int y1, int y2, int color);
void writeLine (int x1, int y1, int x2, int y2, int color);

void writeRect(int x1, int y1, int x2, int y2, int borderWidth, int color);
void writeFilledRect(int x1, int y1, int x2, int y2, int color);
void writeFilledRectWithBorder(int x1, int y1, int x2, int y2, int borderWidth, int color, int colorBorder);

void writeCircle(int x1, int y1, int r, int color);
void writeFilledCircle(int x1, int y1, int r, int color);

void clear();

#endif
