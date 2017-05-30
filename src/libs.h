/** @file libs.h
*@author Larina Anna - anna_larina_99@bk.ru \n
*@author Latyshewa Regina - reggamer@mail.ru*/

#ifndef LIBS_H
#define LIBS_H
#include <stdio.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <time.h>
#include <allegro5/allegro_acodec.h>

#define STARS_ARRAY_SIZE 150
enum MYKEYS {
	KEY_LEFT, KEY_RIGHT
};
static int star[STARS_ARRAY_SIZE][2];
static const float FPS = 60;
static const int SCREEN_W = 699;
static const int SCREEN_H = 466;
static const int BOUNCER_SIZE = 200;
static int level = 100;

static int frames_count = 0;
static int life = 3;
static int star_c = 0;
#endif