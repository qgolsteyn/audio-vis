#include <unistd.h>
#include "DE1_SOC_graphics.h"
#include "DE1_SOC_internal.h"


#ifdef SIM_CODE

#include <pthread.h>
#include "gfx.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void setColor(int color)
{
	switch (color) {
	case	BLACK:
		gfx_color(0,0,0);
		break;
	case	WHITE:
		gfx_color(255,255,255);
		break;
	case RED:
		gfx_color(255,0,0);
		break;
	case	LIME:
		gfx_color(25,100,0);
		break;
	case BLUE:
		gfx_color(51, 65, 133);
		break;
	case YELLOW:
		gfx_color(255,255,0);
		break;
	case CYAN:
		gfx_color(0,255,255);
		break;
	case MAGENTA:
		gfx_color(255,0,255);
		break;
	}
}

void DE1_writePixel (int x, int y, int Colour)
{
	if(delay_graphics)
		usleep(50);

  pthread_mutex_lock(&mutex);
	if(x < 0 || x > 799 || y < 0 || y > 479)
		return;

	setColor(Colour);
	gfx_line(x,y,x,y);
  pthread_mutex_unlock(&mutex);
}

void DE1_writeHLine (int y, int x1, int x2, int Colour)
{
	if(delay_graphics)
		usleep(50);

  pthread_mutex_lock(&mutex);
	if(x1 < 0) x1 = 0;
	if(x1 > 799) x1 = 799;

	if(x2 < 0) x2 = 0;
	if(x2 > 799) x2 = 799;

	if(y < 0) y = 0;
	if(y > 479) y = 479;

	setColor(Colour);
	gfx_line(x1 , y, x2, y);
  pthread_mutex_unlock(&mutex);
}

void DE1_writeVLine (int x, int y1, int y2, int Colour)
{
	if(delay_graphics)
		usleep(50);

  pthread_mutex_lock(&mutex);
	if(y1 < 0) y1 = 0;
	if(y1 > 479) y1 = 479;

	if(y2 > 0) y2 = 0;
	if(y2 > 479) y2 = 479;

	if(x < 0) x = 0;
	if(x > 799) x = 799;

	setColor(Colour);
	gfx_line(x, y1, x, y2);
  pthread_mutex_unlock(&mutex);
}

void DE1_writeLine (int x1, int y1, int x2, int y2, int color)
{
	if(delay_graphics)
		usleep(50);

  pthread_mutex_lock(&mutex);
	setColor(color);
	gfx_line(x1, y1, x2, y2);
  pthread_mutex_unlock(&mutex);
}

void DE1_writeRect (int x1, int y1, int x2, int y2, int color)
{
	if(delay_graphics)
		usleep(50);

  pthread_mutex_lock(&mutex);
	setColor(color);
	gfx_rect(x1, y1, x2, y2);
  pthread_mutex_unlock(&mutex);
}

void Internal_writeFilledRect(int x1, int y1, int x2, int y2, int color)
{
  pthread_mutex_lock(&mutex);
  int i;
  setColor(color);
	for(i = y1; i < y2; i++)
	{
		gfx_line(x1, i, x2, i);
	}
  pthread_mutex_unlock(&mutex);
}

#else

void DE1_writePixel (int x, int y, int Colour)
{
	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	GraphicsX1Reg = x;			// write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsColourReg = Colour;		// set pixel colour with a palette number
	GraphicsCommandReg = PutAPixel;		// give graphics a "write pixel" command
}

void DE1_writeHLine (int y, int x1, int x2, int Colour)
{
	if(x1 < 0) x1 = 0;
	if(x1 > 799) x1 = 799;

	if(x2 < 0) x2 = 0;
	if(x2 > 799) x2 = 799;

	if(y < 0) y = 0;
	if(y > 479) y = 479;

	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	GraphicsX1Reg = x1;			// write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsX2Reg = x2;			// write coords to x2, y2
	GraphicsY2Reg = y;

	GraphicsColourReg = Colour;		// set pixel colour with a palette number
	GraphicsCommandReg = DrawHLine;		// give graphics a "draw H line" command
}

void DE1_writeVLine (int x, int y1, int y2, int Colour)
{
	if(y1 < 0) y1 = 0;
	if(y1 > 479) y1 = 479;

	if(y2 > 0) y2 = 0;
	if(y2 > 479) y2 = 479;

	if(x < 0) x = 0;
	if(x > 799) x = 799;

	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	GraphicsX1Reg = x;			// write coords to x1, y1
	GraphicsY1Reg = y1;
	GraphicsX2Reg = x;			// write coords to x2, y2
	GraphicsY2Reg = y2;

	GraphicsColourReg = Colour;		// set pixel colour with a palette number
	GraphicsCommandReg = DrawVLine;		// give graphics a "draw H line" command
}

void DE1_writeLine (int x1, int y1, int x2, int y2, int color)
{
	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	GraphicsX1Reg = x1;			// write coords to x1, y1
	GraphicsY1Reg = y1;
	GraphicsX2Reg = x2;			// write coords to x2, y2
	GraphicsY2Reg = y2;

	GraphicsColourReg = color;		// set pixel colour with a palette number
	GraphicsCommandReg = DrawLine;		// give graphics a "draw H line" command
}

void DE1_writeRect (int x1, int y1, int x2, int y2, int color)
{
	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	GraphicsX1Reg = x1;			// write coords to x1, y1
	GraphicsY1Reg = y1;
	GraphicsX2Reg = x2;			// write coords to x2, y2
	GraphicsY2Reg = y2;

	GraphicsColourReg = color;		// set pixel colour with a palette number
	GraphicsCommandReg = DrawRect;		// give graphics a "draw H line" command
}

#endif
