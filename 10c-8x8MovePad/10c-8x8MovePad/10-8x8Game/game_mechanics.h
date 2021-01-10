#pragma once

#include <chrono>
#include <stdbool.h>

struct blockInfo {

	int x;
	int y;
	int color;
};

typedef struct blockInfo blockType;

void drawBlocks();

