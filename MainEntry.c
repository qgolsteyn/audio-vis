#include <stdio.h>
#include <unistd.h>

#include "DE1_SOC_touchscreen.h"

#include "ScreenView.h"
#include "Renderer.h"
#include "TouchEventHandler.h"
#include "Bounds.h"
#include "ListView.h"
#include "Button.h"
#include "ProgressBar.h"

#include "TestLib.h"

struct Renderer renderer;
struct TouchEventHandler touchHandler;
void* rootView;

void init(int argc, char* argv[])
{
#ifndef NDEBUG
	testAll();
#endif

	initScreenView();
	initListView();
	initButton();
	initProgressBar();

	DE1_touchInit();

	//Init renderer
	renderer.displayWidth = 800;
	renderer.displayHeight = 480;
	renderer.damagedRegion = 0;

	//Init touch renderer
	touchHandler.head = 0;
	touchHandler.tail = 0;

	//Init root view
	rootView = new(ScreenView, 800, 480, BLUE);
	touchHandler.rootView = rootView;
	setRoot(&renderer, rootView);
	setRenderer(rootView, &renderer);
}

int main(int argc, char* argv[])
{
	init(argc, argv);

	//Audio Screen Init
	void* audioScreen = new(ScreenView, 800, 80, WHITE);
	setX(audioScreen, 0);
	setY(audioScreen, 400);

	attachView(rootView, audioScreen);

	void* playButton = new(Button, BLUE, BLACK);
	setX(playButton, 10);
	setY(playButton, 10);
	setWidth(playButton, 60);
	setHeight(playButton, 60);

	attachView(audioScreen, playButton);

	void* prevButton = new(Button, BLUE, BLACK);
	setX(prevButton, 80);
	setY(prevButton, 10);
	setWidth(prevButton, 60);
	setHeight(prevButton, 60);

	attachView(audioScreen, prevButton);

	void* nextButton = new(Button, BLUE, BLACK);
	setX(nextButton, 150);
	setY(nextButton, 10);
	setWidth(nextButton, 60);
	setHeight(nextButton, 60);

	attachView(audioScreen, nextButton);

	void* progressBar = new(ProgressBar, BLUE);
	setX(progressBar, 220);
	setY(progressBar, 10);
	setWidth(progressBar, 500);
	setHeight(progressBar, 60);

	attachView(audioScreen, progressBar);

	//Menu Screen Init
	void* menuScreen = new(ScreenView, 560, 300, WHITE);
	setX(menuScreen, 100);
	setY(menuScreen, 50);

	attachView(rootView, menuScreen);

	void* menuButton = new(Button, BLUE, BLACK);
	setX(menuButton, 730);
	setY(menuButton, 10);
	setWidth(menuButton, 60);
	setHeight(menuButton, 60);

	inline int onMenuClick(void* _self) {
		struct View* self = menuScreen;
		setVisible(self, !self->visible);
		return 1;
	}

	addEventListener(menuButton, CLICK_EVENT, onMenuClick);

	attachView(audioScreen, menuButton);

	render(&renderer);

	while(1) {
		handleTouch(&touchHandler);
		partialRender(&renderer);
		usleep(1000000/60);
	}

	return 0;
}
