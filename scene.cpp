#include "scene.h"
#include "scene.h"


ALLEGRO_FONT *fight_font = NULL;
ALLEGRO_FONT *store_font = NULL;
ALLEGRO_FONT *restart_font = NULL;
ALLEGRO_FONT *exit_font = NULL;

int place=1;

ALLEGRO_BITMAP *start_background = NULL; //start
ALLEGRO_BITMAP *background = NULL; //fight
ALLEGRO_BITMAP *store_background = NULL; //store

//store
ALLEGRO_BITMAP *skill = NULL;
ALLEGRO_FONT *skill1 = NULL;
ALLEGRO_FONT *skill2 = NULL;
ALLEGRO_FONT *skill3 = NULL;
ALLEGRO_FONT *skill4 = NULL;
ALLEGRO_FONT *hero_blood_font = NULL;
ALLEGRO_FONT *monster_blood_font = NULL;


// function of menu
void menu_init(){  //step 4
    fight_font = al_load_ttf_font("./font/pirulen.ttf",22,0);
    restart_font = al_load_ttf_font("./font/pirulen.ttf",22,0);
    store_font = al_load_ttf_font("./font/pirulen.ttf",22,0);
    exit_font = al_load_ttf_font("./font/pirulen.ttf",22,0);
    start_background = al_load_bitmap("./image/start.jpg");
}


void menu_process(ALLEGRO_EVENT event){  //step 7
    while(event.type == ALLEGRO_EVENT_KEY_UP){
        if( event.keyboard.keycode == ALLEGRO_KEY_W )
            place = place-1;
        else if( event.keyboard.keycode == ALLEGRO_KEY_S )
            place = place+1;
        else if(event.keyboard.keycode == ALLEGRO_KEY_ENTER)
            judge_next_window = true;
            break;}
    if(place<1) place=1;
    if(place>4) place=4;

}


void menu_draw(){//printf("OK\n");
    al_draw_bitmap(start_background, 0, 0, 0);
    //al_clear_to_color(al_map_rgb(100,100,100));

    //fight
    al_draw_filled_rectangle(WIDTH/2-150, 360, WIDTH/2+150, 400, al_map_rgb(255, 255, 255));
    al_draw_text(fight_font, al_map_rgb(0,0,0), WIDTH/2, 365, ALLEGRO_ALIGN_CENTRE, "Fight!");

    //store
    al_draw_filled_rectangle(WIDTH/2-150, 420, WIDTH/2+150, 460, al_map_rgb(255, 255, 255));
    al_draw_text(store_font, al_map_rgb(0,0,0), WIDTH/2, 425, ALLEGRO_ALIGN_CENTRE, "Store");

    //restart
    al_draw_filled_rectangle(WIDTH/2-150, 480, WIDTH/2+150, 520, al_map_rgb(255, 255, 255));
    al_draw_text(restart_font, al_map_rgb(0,0,0), WIDTH/2, 485 , ALLEGRO_ALIGN_CENTRE, "Restart");


    //exit
    al_draw_filled_rectangle(WIDTH/2-150, 540, WIDTH/2+150, 580, al_map_rgb(255, 255, 255));
    al_draw_text(exit_font, al_map_rgb(0,0,0), WIDTH/2, 545, ALLEGRO_ALIGN_CENTRE, "Exit");


}
void menu_destroy(){
    al_destroy_font(fight_font);
    al_destroy_font(restart_font);
    al_destroy_font(store_font);
    al_destroy_font(exit_font);
}

// function of game_scene
void game_scene_init(){
    hero_blood_font = al_load_ttf_font("./font/pirulen.ttf",22,0);
    monster_blood_font = al_load_ttf_font("./font/pirulen.ttf",22,0);
    character_init();
   // printf("character init\n");
    hero_blood_init();
    monster_blood_init();
    background = al_load_bitmap("./image/fight.png");
    monster_init();
  //  printf("monster init\n");
}


void game_process(ALLEGRO_EVENT event){
    if(win_state==0){
        if(hp<=0&&monster_hp<=c){//printf("YOU DIE.\n");
            hp=10;
            monster_hp=0;
            a=100;b=300;c=500;
            judge_next_window=true;
            place=6;
        }
        else if(monster_hp>=c&&hp>=0){//printf("You win!\n");
            money+=500;
            win_state++;
            hp=10;
            monster_hp=0;
            a=30;b=50;c=70;
            judge_next_window=true;
            place=6;printf("Money:%d\n",money);
        }
    }else if(win_state==1){
        if(hp<=0&&monster_hp<=c){//printf("YOU DIE.\n");
            judge_next_window=true;
            hp=10;
            monster_hp=0;
            a=3;b=5;c=7;
            place=6;
            }
        else if(monster_hp>=c&&hp>=0){//printf("You win!\n");
            money+=500;
            win_state++;
            monster_hp=0;
            a=5;b=9;c=14;
            hp=10;
            judge_next_window=true;
            place=6;printf("Money:%d\n",money);
        }

    }else if(win_state==2){
        if(hp<=0&&monster_hp<=c){//printf("YOU DIE.\n");
            judge_next_window=true;
            hp=10;
            monster_hp=0;
            a=5;b=9;c=14;
            place=6;
        }
        else if((monster_hp>=c&&hp>=0)){//printf("You win!\n");
            win_state++;
            judge_next_window=true;
            place=7;//YOU WIN!  RESTART?

        }
    }


}

void game_scene_draw(){
    al_draw_bitmap(background, 0, 0, 0);
    character_draw();
    monster_draw();
    hero_blood_draw();
    monster_blood_draw();
    al_flip_display();

    //hero_blood
    al_draw_filled_rectangle(WIDTH/2-450, 50, WIDTH/2-250, 80, al_map_rgb(255, 255, 255));
    al_draw_text(hero_blood_font, al_map_rgb(0,0,0), WIDTH/2-350, 50, ALLEGRO_ALIGN_CENTRE, "Blood");

    //monster_blood
    al_draw_filled_rectangle(WIDTH/2+450, 50, WIDTH/2+250, 80, al_map_rgb(255, 255, 255));
    al_draw_text(monster_blood_font, al_map_rgb(0,0,0), WIDTH/2+350, 50, ALLEGRO_ALIGN_CENTRE, "Blood");
}

void game_scene_destroy(){
    al_destroy_font(hero_blood_font);
    al_destroy_font(monster_blood_font);

    al_destroy_bitmap(background);
    character_destory();
    monster_destory();
    hero_blood_destory();
    monster_blood_destory();
}

// function of store_scene
void store_scene_init(){
    character_init();
    store_background = al_load_bitmap("./image/store.png");
    skill = al_load_bitmap("./image/skill.png");

    skill1 = al_load_ttf_font("./font/pirulen.ttf",22,0);
    skill2 = al_load_ttf_font("./font/pirulen.ttf",22,0);
    skill3 = al_load_ttf_font("./font/pirulen.ttf",22,0);
    skill4 = al_load_ttf_font("./font/pirulen.ttf",22,0);
}

void store_process(ALLEGRO_EVENT event){
    //printf("storeproc");
    while(event.type == ALLEGRO_EVENT_KEY_UP){
      if(money>=500){
        if( event.keyboard.keycode == ALLEGRO_KEY_W ){
            aatk += 1;
            money -=500;
            printf("Money:%d\n",money);
            break;
            }
        else if( event.keyboard.keycode == ALLEGRO_KEY_A ){
            frog_or_not = true;
            money-=500;
            printf("Money:%d\n",money);
            break;
            }
        else if( event.keyboard.keycode == ALLEGRO_KEY_ENTER){
            judge_next_window = true;
            place = 5;
            break;
            }
        }
     if(money>=1000){
        if( event.keyboard.keycode == ALLEGRO_KEY_S ){
            aatk += 2;
            money -= 1000;
           printf("Money:%d\n",money);
            break;
            }
        else if( event.keyboard.keycode == ALLEGRO_KEY_D ){
            aatk += 0;
            money -= 1000;
            printf("Money:%d\n",money);
            break;}
        else if( event.keyboard.keycode == ALLEGRO_KEY_ENTER){
            judge_next_window = true;
            place = 5;
            break;}
        }else{
            judge_next_window = true;
            place = 5;
            break;
        }

    }

}

ALLEGRO_BITMAP *fin_background = NULL;

void fin_init(){  //step 4
    fin_background = al_load_bitmap("./image/fin.jpg");
}
void fin_draw(){
    al_draw_bitmap(fin_background, 0, 0, 0);
}
void fin_destroy(){
    al_destroy_bitmap(fin_background);
}



void store_scene_draw(){
    al_draw_bitmap(store_background, 0, 0, 0);
    al_draw_bitmap(skill,180,70,0);
    al_draw_bitmap(skill,180,200,0);
    al_draw_bitmap(skill,180,330,0);
    al_draw_bitmap(skill,180,460,0);

    //skill 1
    al_draw_filled_rectangle(280, 110, 650, 135, al_map_rgba(101, 101, 101, 0.3));
    al_draw_text(skill1, al_map_rgb(0,0,0), 285, 110, ALLEGRO_ALIGN_LEFT, "(w)  Smelly feet $500");

    //skill 2
    al_draw_filled_rectangle(280, 240, 650, 265, al_map_rgba(101, 101, 101, 0.3));
    al_draw_text(skill1, al_map_rgb(0,0,0), 285, 240, ALLEGRO_ALIGN_LEFT, "(a)  Frog $500");

    //skill 3
    al_draw_filled_rectangle(280, 370, 650, 395, al_map_rgba(101, 101, 101, 0.3));
    al_draw_text(skill1, al_map_rgb(0,0,0), 285, 370, ALLEGRO_ALIGN_LEFT, "(s)  Bad breath $1000");

    //skill 4
    al_draw_filled_rectangle(280, 500, 650, 525, al_map_rgba(101, 101, 101, 0.3));
    al_draw_text(skill1, al_map_rgb(0,0,0), 285, 500, ALLEGRO_ALIGN_LEFT, "(d)  Heartbreak $1000");


    character_draw();
    al_flip_display();
}
void store_scene_destroy(){

    al_destroy_bitmap(store_background);
    al_destroy_bitmap(skill);


    al_destroy_font(skill1);
    al_destroy_font(skill2);
    al_destroy_font(skill3);
    al_destroy_font(skill4);
    character_destory();//printf("OK\n");
}

