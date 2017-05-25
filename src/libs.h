#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <time.h>
#include <allegro5/allegro_acodec.h>

enum MYKEYS {
	KEY_LEFT, KEY_RIGHT
};
int star[STARS_ARRAY_SIZE][2] = { -1 };
const float FPS = 60;
const int SCREEN_W = 699;
const int SCREEN_H = 466;
const int BOUNCER_SIZE = 200;
int level = 100;


int count = 0;
int frames_count = 0;
int life = 3;
int star_c = 0;