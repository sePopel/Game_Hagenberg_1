#include <stdio.h>
#include <stdlib.h>


#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "canvas.h"
#include "game_mechanics.h"

bool aPressed = false;
bool sPressed = false;

#define WINDOW_X	100
#define WINDOW_Y	100

#define WINDOW_WIDTH	1024
#define WINDOW_HEIGHT	1024

#define RESOLUTION_X	16
#define RESOLUTION_Y	16

int xPad = 4;
auto old = std::chrono::steady_clock::now();

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

void drawPad() {
	// remove old Pos


	pixels[xPad][0] = 0;
	auto act = std::chrono::steady_clock::now();
	double elapsed_time = double(std::chrono::duration_cast <std::chrono::nanoseconds> (act - old).count());

	if (sPressed && xPad < RESOLUTION_X - 1) {
		if (elapsed_time > 100000000) {
			xPad++;
			old = act;
		}
	}

	if (aPressed && xPad > 0)
		if (elapsed_time > 100000000) {
			xPad--;
			old = act;
		}


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