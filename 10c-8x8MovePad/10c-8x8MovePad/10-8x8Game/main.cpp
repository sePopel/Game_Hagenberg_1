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
bool bPressed = false;
bool nPressed = false;
bool mPressed = false;
bool b = false;

#define WINDOW_X	100
#define WINDOW_Y	100

#define WINDOW_WIDTH	1024
#define WINDOW_HEIGHT	1024

#define RESOLUTION_X	16
#define RESOLUTION_Y	16

#define min(a,b) (((a) < (b)) ? (a) : (b))

int xPad = 8;
int x_1 = 8;
int y_1 = 15;

double timeblock = 20;
double timemove = 10;
double timepad = 1;

/*blockType Nr_1;
blockType Nr_2;
blockType Nr_3;
blockType Nr_4;
blockType Nr_5;
blockType Nr_6;

shotType B;
*/







auto oldPad = std::chrono::steady_clock::now();
auto oldblock = std::chrono::steady_clock::now();
auto oldcopy = std::chrono::steady_clock::now();
auto oldshoot_move = std::chrono::steady_clock::now();
auto oldshot = std::chrono::steady_clock::now();
//auto oldmove = std::chrono::steady_clock::now();

auto act = (std::chrono::steady_clock::now());

unsigned char pixels[RESOLUTION_X][RESOLUTION_Y] [2];
unsigned char last[RESOLUTION_Y];


void initPixels()
{
	for (int i = 0; i < RESOLUTION_X; i++)
	{
		for (int j = 0; j < RESOLUTION_Y; j++)
		{
			pixels[i][j][0] = 0;
			pixels[i][j][1] = 0;
		}
	}
}


void updatePixels()
{
	for (int i = 0; i < RESOLUTION_X; i++)
	{
		for (int j = 0; j < RESOLUTION_Y; j++)
		{ 
			if (pixels[i][j][0] >= 2 && pixels[i][j][1] >= 2) {
				
				int r1 = 0;
				int g1 = 0;
				int b1 = 0;

				int r2 = 0;
				int g2 = 0;
				int b2 = 0;
				
				/*if ((pixels[i + 1][j][0] >= 2)) {

					if (pixels[i + 1][j][0] == 2) {
						r1 = 255;
					}
					if (pixels[i + 1][j][0] == 3) {
						g1 = 255;
					}
					if (pixels[i + 1][j][0] == 4) {
						b1 = 255;
					}
					if (pixels[i + 1][j][0] == 5) {
						r1 = 255;
						g1 = 255;
					}
					if (pixels[i + 1][j][0] == 6) {
						r1 = 255;
						b1 = 255;
					}
					if (pixels[i + 1][j][0] == 7) {
						g1 = 255;
						b1 = 255;
					}

					if (pixels[i][j][1] == 2) {
						r2 = 255;
					}
					if (pixels[i][j][1] == 3) {
						g2 = 255;
					}
					if (pixels[i][j][1] == 4) {
						b2 = 255;
					}
					if (pixels[i][j][1] == 5) {
						r2 = 255;
						g2 = 255;
					}
					if (pixels[i][j][1] == 6) {
						r2 = 255;
						b2 = 255;
					}
					if (pixels[i][j][1] == 7) {
						g2 = 255;
						b2 = 255;
					}

					int a = min(r1 + r2, 255); //Geht im if nicht :/
					int b = min(g1 + g2, 255);
					int c = min(b1 + b2, 255);


					if (a == 255 && b == 255 && c == 255) {
						pixels[i][j][0] = 0;
					}
					if (a == 255 && b == 0 && c == 0) {
						pixels[i][j][0] = 2;
					}
					if (a == 0 && b == 255 && c == 0) {
						pixels[i][j][0] = 3;
					}
					if (a == 0 && b == 0 && c == 255) {
						pixels[i][j][0] = 4;
					}
					if (a == 255 && b == 255 && c == 0) {
						pixels[i][j][0] = 5;
					}
					if (a == 255 && b == 0 && c == 255) {
						pixels[i][j][0] = 6;
					}
					if (a == 0 && b == 255 && c == 255) {
						pixels[i][j][0] = 7;
					}
				}

				if ((pixels[i - 1][j][0] >= 2)) {
					if (pixels[i - 1][j][0] == 2) {
						r1 = 255;
					}
					if (pixels[i - 1][j][0] == 3) {
						g1 = 255;
					}
					if (pixels[i - 1][j][0] == 4) {
						b1 = 255;
					}
					if (pixels[i - 1][j][0] == 5) {
						r1 = 255;
						g1 = 255;
					}
					if (pixels[i - 1][j][0] == 6) {
						r1 = 255;
						b1 = 255;
					}
					if (pixels[i - 1][j][0] == 7) {
						g1 = 255;
						b1 = 255;
					}

					if (pixels[i][j][1] == 2) {
						r2 = 255;
					}
					if (pixels[i][j][1] == 3) {
						g2 = 255;
					}
					if (pixels[i][j][1] == 4) {
						b2 = 255;
					}
					if (pixels[i][j][1] == 5) {
						r2 = 255;
						g2 = 255;
					}
					if (pixels[i][j][1] == 6) {
						r2 = 255;
						b2 = 255;
					}
					if (pixels[i][j][1] == 7) {
						g2 = 255;
						b2 = 255;
					}

					int a = min(r1 + r2, 255); //Geht im if nicht :/
					int b = min(g1 + g2, 255);
					int c = min(b1 + b2, 255);


					if (a == 255 && b == 255 && c == 255) {
						pixels[i][j][0] = 0;
					}
					if (a == 255 && b == 0 && c == 0) {
						pixels[i][j][0] = 2;
					}
					if (a == 0 && b == 255 && c == 0) {
						pixels[i][j][0] = 3;
					}
					if (a == 0 && b == 0 && c == 255) {
						pixels[i][j][0] = 4;
					}
					if (a == 255 && b == 255 && c == 0) {
						pixels[i][j][0] = 5;
					}
					if (a == 255 && b == 0 && c == 255) {
						pixels[i][j][0] = 6;
					}
					if (a == 0 && b == 255 && c == 255) {
						pixels[i][j][0] = 7;
					}
				}

				*/

				if (pixels[i][j][0] == 2) {
					r1 = 255;
				}
				if (pixels[i][j][0] == 3) {
					g1 = 255;
				}
				if (pixels[i][j][0] == 4) {
					b1 = 255;
				}
				if (pixels[i][j][0] == 5) {
					r1 = 255;
					g1 = 255;
				}
				if (pixels[i][j][0] == 6) {
					r1 = 255;
					b1 = 255;
				}
				if (pixels[i][j][0] == 7) {
					g1 = 255;
					b1 = 255;
				}
				

				if (pixels[i][j][1] == 2) {
					r2 = 255;
				}
				if (pixels[i][j][1] == 3) {
					g2 = 255;
				}
				if (pixels[i][j][1] == 4) {
					b2 = 255;
				}
				if (pixels[i][j][1] == 5) {
					r2 = 255;
					g2 = 255;
				}
				if (pixels[i][j][1] == 6) {
					r2 = 255;
					b2 = 255;
				}
				if (pixels[i][j][1] == 7) {
					g2 = 255;
					b2 = 255;
				}

				int a = min(r1 + r2, 255); //Geht im if nicht :/
				int b = min(g1 + g2, 255);
				int c = min(b1 + b2, 255);


				if (a == 255 && b == 255 && c == 255) {
					pixels[i][j][0] = 0;
				}
				if (a == 255 && b == 0 && c == 0) {
					pixels[i][j][0] = 2;
				}
				if (a == 0 && b == 255 && c == 0) {
					pixels[i][j][0] = 3;
				}
				if (a == 0 && b == 0 && c == 255) {
					pixels[i][j][0] = 4;
				}
				if (a == 255 && b == 255 && c == 0) {
					pixels[i][j][0] = 5;
				}
				if (a == 255 && b == 0 && c == 255) {
					pixels[i][j][0] = 6;
				}
				if (a == 0 && b == 255 && c == 255) {
					pixels[i][j][0] = 7;
				}
				
				if ((pixels[i + 1][j][0] >= 2)) {
					pixels[i + 1][j][0] = pixels[i][j][0];
				}

				if ((pixels[i - 1][j][0] >= 2)) {
					pixels[i - 1][j][0] = pixels[i][j][0];
				}

				pixels[i][j][1] = 0;
			}

			if (pixels[i][j][0] == 2)
				canvasSetPixel(i, j, 255, 0, 0);
			if (pixels[i][j][0] == 3)
				canvasSetPixel(i, j, 0, 255, 0);
			if (pixels[i][j][0] == 4)
				canvasSetPixel(i, j, 0, 0, 255);
			if(pixels[i][j][0] == 5)
				canvasSetPixel(i, j, 255, 255, 0);
			if (pixels[i][j][0] == 6)
				canvasSetPixel(i, j, 255, 0, 255);
			if (pixels[i][j][0] == 7)
				canvasSetPixel(i, j, 0, 255, 255);
			if (pixels[i][j][0] == 1)
				canvasSetPixel(i, j, 0, 0, 0);
			if (pixels[i][j][0] == 0)
				canvasSetPixel(i, j, 255, 255, 255);

			if (pixels[i][j][1] == 2)
				canvasSetPixel(i, j, 255, 0, 0);
			if (pixels[i][j][1] == 3)
				canvasSetPixel(i, j, 0, 255, 0);
			if (pixels[i][j][1] == 4)
				canvasSetPixel(i, j, 0, 0, 255);
			if (pixels[i][j][1] == 5)
				canvasSetPixel(i, j, 255, 255, 0);
			if (pixels[i][j][1] == 6)
				canvasSetPixel(i, j, 255, 0, 255);
			if (pixels[i][j][1] == 7)
				canvasSetPixel(i, j, 0, 255, 255);
		}
	}
}

/*void mixing() {
	if pixels[]
	
	(r1, g1, b1) + (r2, g2, b2) =
		(min(r1 + r2, 256), min(g1 + g2, 256), min(b1 + b2, 256))
}*/

void drawPad() {
	// remove old Pos


	pixels[xPad][0][0] = 0;
	double elapsed_time = double(std::chrono::duration_cast <std::chrono::nanoseconds> (act - oldPad).count());

	if (sPressed && xPad < RESOLUTION_X - 1) {
		if (elapsed_time > (timepad) * 100000000) {
			xPad++;
			oldPad = act;
		}
	}

	if (aPressed && xPad > 0) {
		if (elapsed_time > (timepad) * 100000000) {
			xPad--;
			oldPad = act;
		}
	}

	pixels[xPad][0][0] = 1;
}

bool colorLine16() {
	for (int i = 0; i < 16; i++) {
		if (last[i]>1){
			return true;
		}
	}
	return false;
}

void moveBlocks() {
	
	double elapsed_time = double(std::chrono::duration_cast <std::chrono::nanoseconds> (act - oldcopy).count());

	if (elapsed_time > (timemove) * 100000000) {
		for (int j = 1; j < 17; j++) {
			for (int i = 0; i < 16; i++) {

				if (j == 16) {

					pixels[i][15][0] = 0;
					continue;
				}

				if (j == 1) {

					last[i] = pixels[i][j][0];
					continue;
				}

				pixels[i][j - 1][0] = pixels[i][j][0];
			}
		}

		oldcopy = act;
	}
}

void drawBlocks() {

	
	double elapsed_time_block = double(std::chrono::duration_cast <std::chrono::nanoseconds> (act - oldblock).count());
	//double elapsed_time_move = double(std::chrono::duration_cast <std::chrono::nanoseconds> (act - oldmove).count());

	if (elapsed_time_block > (timeblock) * 100000000) {
			x_1 = rand() % 16;
			int color_1 = (rand() % 6) + 2;
			oldblock = act;
			pixels[x_1][y_1][0] = color_1;

			
			if (rand() % 2 == 1) {
				if (x_1 < RESOLUTION_X-1)
				pixels[x_1 + 1][y_1][0] = color_1;
			}
	}

	/*if (elapsed_time_move > (timemove) * 100000000) {
		Nr_1.y--;
		Nr_2.y--;
		Nr_3.y--;
		Nr_4.y--;
		Nr_5.y--;
		Nr_6.y--;

		oldmove = newblock;
	}*/
	
	/*pixels[Nr_1.x][Nr_1.y] = Nr_1.color;
	pixels[Nr_2.x][Nr_2.y] = Nr_2.color;
	pixels[Nr_3.x][Nr_3.y] = Nr_3.color;
	pixels[Nr_4.x][Nr_4.y] = Nr_4.color;
	pixels[Nr_5.x][Nr_5.y] = Nr_5.color;
	pixels[Nr_6.x][Nr_6.y] = Nr_6.color;*/
}

/*void shoot() {

	double elapsed_time = double(std::chrono::duration_cast <std::chrono::nanoseconds> (act - oldshoot_move).count());
	
	for (int i = 0; i < 11;){
		if (bPressed) {
		
			switch (i) {
				case 0:
					B.shot_1.shot = true;
				case 1:
					B.shot_2.shot = true;
				case 2:
					B.shot_3.shot = true;
				case 3:
					B.shot_4.shot = true;
				case 4:
					B.shot_5.shot = true;
				case 5:
					B.shot_6.shot = true;
				case 6:
					B.shot_7.shot = true;
				case 7:
					B.shot_8.shot = true;
				case 8:
					B.shot_9.shot = true;
				case 9:
					B.shot_10.shot = true;
				case 10:
					B.shot_11.shot = true;
			}

		}
	}

	if (b && elapsed_time > (1000) * 100000000) {
		 

		pixels[xPad][B.shot_1.y] = 3;
		shot++;
		pixels[xPad][shot - 1] = 0;

		if (shot == 15) {
			shot = 0;
			b = false;
		}

		oldshoot_move = act;

	}
	
} */

void shoot() {

	double elapsed_time = double(std::chrono::duration_cast <std::chrono::nanoseconds> (act - oldshot).count());
	if (bPressed) {
		pixels[xPad][0][1] = 2 ;
	}

	if (nPressed) {
		pixels[xPad][0][1] = 3;
	}

	if (mPressed) {
		pixels[xPad][0][1] = 4;
	}
	
	if (elapsed_time > (2) * 100000000) {
		
		for (int j = 15; j >= 0; j--) {
			
			for (int i = 0; i < 16; i++) {

				if (j == 0) {

					pixels[i][j][1] = 0;
					continue;
				}

				pixels[i][j][1] = pixels[i][j - 1][1];
			}
		}

		oldshot = act;
	}
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
		act = std::chrono::steady_clock::now();
		drawPad();

		drawBlocks();
		moveBlocks();
		shoot();
		
		
		

		updatePixels();
		repaint();

		if (colorLine16()) {
			printf("Game Over");
			cleanup();
			return EXIT_SUCCESS;
			
		}
	}

	cleanup();
	return EXIT_SUCCESS;

}