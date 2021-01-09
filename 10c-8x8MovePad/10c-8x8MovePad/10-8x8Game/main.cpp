#include <stdio.h>
#include <stdlib.h>


#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "canvas.h"

bool aPressed = false;
bool sPressed = false;

#define WINDOW_X	100
#define WINDOW_Y	100

#define WINDOW_WIDTH	1024
#define WINDOW_HEIGHT	1024

#define RESOLUTION_X	16
#define RESOLUTION_Y	16

int xPad = 4;

unsigned char pixels[RESOLUTION_X][RESOLUTION_Y];


void initPixels()
{
	for (int i = 0; i < RESOLUTION_X; i++)
	{
		for (int j = 0; j < RESOLUTION_Y; j++)
		{
			pixels[i][j] = 0;
		}
	}
}


void updatePixels()
{
	for (int i = 0; i < RESOLUTION_X; i++)
	{
		for (int j = 0; j < RESOLUTION_Y; j++)
		{
			if (pixels[i][j] == 1)
				canvasSetPixel(i, j, 1.0);
			else
				canvasSetPixel(i, j, 0.25);

		}
	}
}

int x;

void drawPad() {
	// remove old Pos


	pixels[xPad][0] = 0;

	if (sPressed && xPad < RESOLUTION_X - 1) {
		x = 0;
		x++;

		if (x != 0 && x%50== 0 ) {
		xPad++;
	}
}

	if (aPressed && xPad > 0)
		xPad--;
	
	pixels[xPad][0] = 1;
}


void cleanup()
{
	canvasClose();
}


int main(int argc, char* argv[])
{
	if (canvasInit(WINDOW_X, WINDOW_Y, WINDOW_WIDTH, WINDOW_HEIGHT, RESOLUTION_X, RESOLUTION_Y))
	{
		printf("ERROR: init failed (invalid argument?)\n");
		return EXIT_FAILURE;
	}

	initPixels();				// initialize buffer with 0

	while (canvasUpdate() == 0)
	{
		drawPad();

		updatePixels();
		repaint();

	}

	cleanup();

	return EXIT_SUCCESS;
}