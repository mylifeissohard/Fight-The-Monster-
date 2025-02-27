#include "scene.h"


ALLEGRO_FONT *hero_blood_font = NULL;
ALLEGRO_FONT *monster_blood_font = NULL;
ALLEGRO_BITMAP *background = NULL;

// function of fight
void game_init(){

    hero_blood_font = al_load_ttf_font("./font/pirulen.ttf",22,0);
    monster_blood_font = al_load_ttf_font("./font/pirulen.ttf",22,0);
    character_init();
    background = al_load_bitmap("./image/fight.png");
}


void game_scene_draw(){

    al_draw_bitmap(background, 0, 0, 0);
    character_draw();
    al_flip_display();


    //hero_blood
    al_draw_filled_rectangle(WIDTH/2-150, 360, WIDTH/2+150, 400, al_map_rgb(255, 255, 255));
    al_draw_text(hero_blood_font, al_map_rgb(0,0,0), WIDTH/2, 365, ALLEGRO_ALIGN_CENTRE, "Blood");

    //monster_blood
    al_draw_filled_rectangle(WIDTH/2-150, 420, WIDTH/2+150, 460, al_map_rgb(255, 255, 255));
    al_draw_text(monster_blood_font, al_map_rgb(0,0,0), WIDTH/2, 425, ALLEGRO_ALIGN_CENTRE, "Blood");

}
void game_scene_destroy(){

    al_destroy_font(hero_blood_font);
    al_destroy_font(monster_blood_font);

    al_destroy_bitmap(background);
    character_destory();
}
/*
// function of game(fight)_scene
void game_scene_init(){
    character_init();
    background = al_load_bitmap("./image/fight.png");
}
void game_scene_draw(){
    al_draw_bitmap(background, 0, 0, 0);
    character_draw();
    al_flip_display();
}
void game_scene_destroy(){
    al_destroy_bitmap(background);
    character_destory();
}*/

