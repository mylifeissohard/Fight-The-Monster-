#include "global.h"
#include "charater.h"

void menu_init();
void menu_process(ALLEGRO_EVENT event);
void menu_draw();
void menu_destroy();

void game_scene_init();
void game_process(ALLEGRO_EVENT event);
void game_scene_draw();
void game_scene_destroy();

void store_scene_init();
void store_process(ALLEGRO_EVENT event);
void store_scene_draw();
void store_scene_destroy();

extern int place;

void fin_init();
void fin_draw();
void fin_destroy();
