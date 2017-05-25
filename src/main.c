#include "libs.h"
#define STARS_ARRAY_SIZE 150
//счётчик звёзд

int main(int argc, char **argv)
{
    srand(time(NULL));
    ALLEGRO_SAMPLE *music = NULL;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *bouncer = NULL;
    float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;//позиция героя по x
    float bouncer_y = SCREEN_H - 50.0 - BOUNCER_SIZE / 2.0;//по у
    bool key[2] = { false, false };
    bool redraw = true; // чтобы не перерисовывалось каждый кадр
    bool exit = false;

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    if (!al_init_image_addon()) {
        fprintf(stderr, "failed to initialize image addon!\n");
        return -1;
    }
    al_init_primitives_addon();


    if (!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }

    if (!al_init_font_addon()) {
        fprintf(stderr, "failed to initialize the fond!\n");
        return -1;
    }
    ALLEGRO_FONT *AllegroFont = al_create_builtin_font();

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);

    ALLEGRO_BITMAP * bmp, *image, *me = NULL;
    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        return -1;
    }
    bmp = al_load_bitmap("cosmos.jpeg");
    if (!bmp)
    {
        printf("ERROR Loading sprite:No file");
        return -1;
    }

    image = al_load_bitmap("zvezda.png");
    int image_W = al_get_bitmap_width(image);
    int image_H = al_get_bitmap_height(image);

    if (!al_install_audio()) {
        fprintf(stderr, "failed to create audio!\n");
        al_destroy_timer(timer);
        return -1;
    }
    if (!al_init_acodec_addon()) {
        fprintf(stderr, "failed to create audio!\n");
        al_destroy_timer(timer);
        return -1;
    }
    /*if (!al_reserve_samples(1)) {
        fprintf(stderr, "failed to create audio!\n");
        al_destroy_timer(timer);
        return -1;
    }*/

    bouncer = al_load_bitmap("kek.png");
    int bouncer_W = al_get_bitmap_width(bouncer);
    int bouncer_H = al_get_bitmap_height(bouncer);
    if (!bouncer) {
        fprintf(stderr, "failed to create bouncer bitmap!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
    for (int i = 0; i < STARS_ARRAY_SIZE; i++) {
        star[i][0] = -1;
        star[i][1] = -1;
    }

    event_queue = al_create_event_queue();
    if (!event_queue) { //регистрация евентов
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_bitmap(bouncer);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);
    gen();
    al_play_sample(music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
    while (!exit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {

            if (key[KEY_LEFT] && bouncer_x >= 4.0) {//когда событие по таймеру
                bouncer_x -= 5.0;
            }

            if (key[KEY_RIGHT] && bouncer_x <= SCREEN_W - 5.0) {
                bouncer_x += 5.0;
            }

            redraw = true;
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { //если нажму крестик
            break;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_LEFT:
                key[KEY_LEFT] = true;
                break;

            case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = true;
                break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_LEFT:
                key[KEY_LEFT] = false;
                break;

            case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = false;
                break;

            case ALLEGRO_KEY_ESCAPE:
                exit = true;
                break;
            }
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_scaled_bitmap(bmp,
                0, 0,
                al_get_bitmap_width(bmp),
                al_get_bitmap_height(bmp),
                0, 0,
                SCREEN_W, SCREEN_H,
                0);


            //   al_draw_scaled_bitmap(bouncer,0, 20, al_get_bitmap_width(bouncer), al_get_bitmap_width(bouncer),
            //   bouncer_x, bouncer_y, 85, 95, 0);
            frames_count++;
            if (frames_count >= level)
            {
                level--;
                frames_count = 0;
                if (life > 0)
                    gen();
            }
            if (life == 0) {
                al_draw_textf(AllegroFont, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "GAME OVER!!! Total score: %i", star_c);
            };

            for (int i = 0; i < STARS_ARRAY_SIZE; i++) {
                if (star[i][0] >= 0)
                {

                    al_draw_scaled_bitmap(image,
                        0, 0, al_get_bitmap_width(image), al_get_bitmap_width(image),
                        star[i][0], star[i][1], 40, 40, 0);

                    if (life > 0)
                        star[i][1] += 2;
                    int c = star[i][1] - bouncer_y;
                    if (c < 0)
                        c *= -1;
                    if (c < 5)
                    {
                        int r = star[i][0] - bouncer_x;
                        if (r < 0) { r *= -1; }
                        if (r < 60)
                        {
                            star[i][0] = -1;
                            star_c++;
                        }
                        else {
                            life -= 1;
                            star[i][0] = -1;
                        }

                    }
                }
            }

            al_draw_textf(AllegroFont, al_map_rgb(0, 0, 0), SCREEN_W - 40, SCREEN_H - 25, ALLEGRO_ALIGN_RIGHT, "STARS COLLECTED:%i", star_c);
            al_draw_textf(AllegroFont, al_map_rgb(0, 0, 0), SCREEN_W - 610, SCREEN_H - 25, ALLEGRO_ALIGN_RIGHT, "LIFE:%i", life);

            al_flip_display();
        }


    }

    al_destroy_bitmap(bouncer);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_sample(music);

    return 0;
}