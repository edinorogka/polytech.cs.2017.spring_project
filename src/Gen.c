#include "libs.h"
void gen() {
	int i;
	int x;
	{
		if (count >= STARS_ARRAY_SIZE) {
			count = 0;
		}
		star[count][0] = (rand() % (SCREEN_W - 100) + 50);
		star[count++][1] = 0;
		star[count][0] = -1;
		star[count][1] = -1;
	}
}