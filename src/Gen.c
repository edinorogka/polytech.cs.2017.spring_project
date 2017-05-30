#include "libs.h"
int count = 0;

void gen( int star[STARS_ARRAY_SIZE][2]) {
	int i;
	int x;
	if (count >= STARS_ARRAY_SIZE) {
		count = 0;
	}
	{
		star[count][0] = (rand() % (SCREEN_W - 100) + 50);
		star[count++][1] = 0;
		star[count][0] = -1;
		star[count][1] = -1; }
}