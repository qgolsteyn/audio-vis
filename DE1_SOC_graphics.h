#ifndef DE1_SOC_GRAPHICS_H_
#define DE1_SOC_GRAPHICS_H_

#define XRES 800
#define YRES 480

#define DrawHLine		1
#define DrawVLine		2
#define DrawLine		3
#define DrawRect		4
#define PutAPixel		0xA
#define GetAPixel		0xB
#define ProgramPaletteColour   	0x10

#define WAIT_FOR_GRAPHICS		while((GraphicsStatusReg & 0x0001) != 0x0001);

#define GraphicsCommandReg   		(*(volatile unsigned short int *)(0x84000000))
#define GraphicsStatusReg   		(*(volatile unsigned short int *)(0x84000000))
#define GraphicsX1Reg   		(*(volatile unsigned short int *)(0x84000002))
#define GraphicsY1Reg   		(*(volatile unsigned short int *)(0x84000004))
#define GraphicsX2Reg   		(*(volatile unsigned short int *)(0x84000006))
#define GraphicsY2Reg			(*(volatile unsigned short int *)(0x84000008))
#define GraphicsColourReg		(*(volatile unsigned short int *)(0x8400000E))
#define GraphicsBackGroundColourReg   		(*(volatile unsigned short int *)(0x84000010))

#define	BLACK		0
#define	WHITE		1
#define	RED			2
#define	LIME		3
#define	BLUE		4
#define	YELLOW		5
#define	CYAN		6
#define	MAGENTA		7

void DE1_writePixel(int x, int y, int color);
void DE1_writeHLine (int y, int x1, int x2, int color);
void DE1_writeVLine (int x, int y1, int y2, int Colour);
void DE1_writeLine (int x1, int y1, int x2, int y2, int color);
void DE1_writeRect (int x1, int y1, int x2, int y2, int color);

#endif
