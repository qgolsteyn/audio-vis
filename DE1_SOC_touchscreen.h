#ifndef DE1_SOC_TOUCHSCREEN_H_
#define DE1_SOC_TOUCHSCREEN_H_

struct Point {
  int status;
  int x;
  int y;
};

#ifndef SIM_CODE
#define TOUCH_CONTROL (*(volatile unsigned char *)(0x84000230))
#define TOUCH_STATUS (*(volatile unsigned char *)(0x84000230))
#define TOUCH_TXDATA (*(volatile unsigned char *)(0x84000232))
#define TOUCH_RXDATA (*(volatile unsigned char *)(0x84000232))
#define TOUCH_BAUD 	(*(volatile unsigned char *)(0x84000234))
#endif

#define NONE 0;
#define PRESSED 1;
#define RELEASED 2;

void DE1_touchInit();
int DE1_isScreenTouched();
struct Point DE1_getLastTouchLocation();

#endif
