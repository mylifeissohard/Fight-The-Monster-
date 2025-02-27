#include "charater.h"

// the state of character
enum {STOP = 0, MOVE, ATK};
enum {STOPP= 0, MOVEE, ATKK};
typedef struct character
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[2];
    ALLEGRO_BITMAP *img_atk[2];
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
}Character;
Character chara;
//The state of monster
Character chard;

ALLEGRO_SAMPLE *sample = NULL;
//int q=1;
void character_init(){
    // load character images
   if(frog_or_not == false){
        for(int i = 1 ; i <= 2 ; i++){
        char temp[500];
        sprintf( temp, "./image/char_move%d.png", i );
        chara.img_move[i-1] = al_load_bitmap(temp);
        }
        for(int i = 1 ; i <= 2 ; i++){
            char temp[500];
            sprintf( temp, "./image/char_atk%d.png", i );
            chara.img_atk[i-1] = al_load_bitmap(temp);
        }//printf("character init%d OK\n",q);q++;
    }
   if(frog_or_not == true){
        for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/frog%d.png", 1 );
        chara.img_move[i-1] = al_load_bitmap(temp);
        }
        for(int i = 1 ; i <= 2 ; i++){
            char temp[50];
            sprintf( temp, "./image/frog%d.png", i );
            chara.img_atk[i-1] = al_load_bitmap(temp);
        }
        }

    // load effective sound
    sample = al_load_sample("./sound/atk_sound.wav");
    chara.atk_Sound  = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(chara.atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(chara.atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);
    chara.y = 450;
    chara.x = 0;
    chara.dir = true;

    // initial the animation component
    chara.state = STOP;
    chara.anime = 0;
    chara.anime_time = 30;

}
void charater_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chara.anime++;
            chara.anime %= chara.anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        chara.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}
//int p=1;
void charater_update(){//printf("character blood:%d\n",hp);
    // use the idea of finite state machine to deal with different state

    if( key_state[ALLEGRO_KEY_W] ){
        chara.y -= 5;
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_A] ){
        chara.dir = false;
        chara.x -= 5;
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_S] ){
        chara.y += 5;
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_D] ){
        chara.dir = true;
        chara.x += 5;
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_SPACE] ){
        chara.state = ATK;
    }else if( chara.anime == chara.anime_time-1 ){
        chara.anime = 0;
        chara.state = STOP;
    }else if ( chara.anime == 0 ){
        chara.state = STOP;
    }
    if(chard.state==ATKK){//monster atk
        hp-=1;
    }

}

void character_draw(){
    // with the state, draw corresponding image
    if( chara.state == STOP ){
        if( chara.dir )
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
    }else if( chara.state == MOVE ){
        if( chara.dir ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }else{
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
            }else{
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, 0);
            }
        }
    }else if( chara.state == ATK ){
        if( chara.dir ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_atk[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara.img_atk[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
                al_play_sample_instance(chara.atk_Sound);
            }
        }else{
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_atk[0], chara.x, chara.y, 0);
            }else{
                al_draw_bitmap(chara.img_atk[1], chara.x, chara.y, 0);
                al_play_sample_instance(chara.atk_Sound);
            }
        }

    }
}
void character_destory(){
    al_destroy_bitmap(chara.img_atk[0]);
    al_destroy_bitmap(chara.img_atk[1]);
    al_destroy_bitmap(chara.img_move[0]);
    al_destroy_bitmap(chara.img_move[1]);
    al_destroy_sample_instance(chara.atk_Sound);
}




// the state of hero blood
enum {Blood1=0,Blood2,Blood3,Blood4};//Blood1=full,Blood4=empty
typedef struct Blood
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img_blood[4];
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int state;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
}Blood;
Blood charb;

void hero_blood_init(){
    // load blood images
    for(int i = 1 ; i <= 4 ; i++){
        char temp[500];
        sprintf( temp, "./image/blood%d.jpg",i);
        charb.img_blood[i-1] = al_load_bitmap(temp);
    }


    // initial the geometric information of character
    charb.width = al_get_bitmap_width(charb.img_blood[0]);
    charb.height = al_get_bitmap_height(charb.img_blood[0]);
    charb.x = WIDTH/2-440;
    charb.y = HEIGHT/2-230;

    // initial the animation component
    charb.state = Blood1;
    charb.anime = 0;
    charb.anime_time = 30;

}


void hero_blood_update(){
    // use the idea of finite state machine to deal with different state
    if(hp==7){
        charb.state=Blood2;
        }
    else if(hp==5){
         charb.state=Blood3;
        }
    else if(hp==3){
         charb.state=Blood4;
        }

}
void hero_blood_draw(){
    // with the state, draw corresponding image
    if( charb.state == Blood1 ){
            al_draw_bitmap(charb.img_blood[0], charb.x, charb.y, 0);
        }
    else if( charb.state == Blood2 ){
            al_draw_bitmap(charb.img_blood[1], charb.x, charb.y, 0);
            //al_play_sample_instance(chara.atk_Sound);
        }
    else if( charb.state == Blood3 ){
            al_draw_bitmap(charb.img_blood[2], charb.x, charb.y, 0);
            //al_play_sample_instance(chara.atk_Sound);
        }
    else if( charb.state == Blood4 ){
            al_draw_bitmap(charb.img_blood[3], charb.x, charb.y, 0);
            //al_play_sample_instance(chara.atk_Sound);
        }
    }

void hero_blood_destory(){
    al_destroy_bitmap(charb.img_blood[0]);
    al_destroy_bitmap(charb.img_blood[1]);
    al_destroy_bitmap(charb.img_blood[2]);
    al_destroy_bitmap(charb.img_blood[3]);

}

// the state of monster blood

Blood charc;

void monster_blood_init(){
    // load blood images
    for(int i = 1 ; i <= 4 ; i++){
        char temp[500];
        sprintf( temp, "./image/blood%d.jpg",i);
        charc.img_blood[i-1] = al_load_bitmap(temp);
    }


    // initial the geometric information of character
    charc.width = al_get_bitmap_width(charc.img_blood[0]);
    charc.height = al_get_bitmap_height(charc.img_blood[0]);
    charc.x = WIDTH/2+260;
    charc.y = HEIGHT/2-230;

    // initial the animation component
    charc.state = Blood1;
    charc.anime = 0;
    charc.anime_time = 30;

}


void monster_blood_update(){
    // use the idea of finite state machine to deal with different state
    if(monster_hp>0&&monster_hp<a){
        charc.state=Blood2;
        }
    else if(monster_hp>=a&&monster_hp<=b){
         charc.state=Blood3;
        }
    else if(monster_hp>=b&&monster_hp<=c){
         charc.state=Blood4;
        }//printf("monster blood %d\n",monster_hp);
}
void monster_blood_draw(){
    // with the state, draw corresponding image
    if( charc.state == Blood1 ){
            al_draw_bitmap(charc.img_blood[0], charc.x, charc.y, 0);
        }
    else if( charc.state == Blood2 ){
            al_draw_bitmap(charc.img_blood[1], charc.x, charc.y, 0);
            //al_play_sample_instance(chara.atk_Sound);
        }
    else if( charc.state == Blood3 ){
            al_draw_bitmap(charc.img_blood[2], charc.x, charc.y, 0);
            //al_play_sample_instance(chara.atk_Sound);
        }
    else if( charc.state == Blood4 ){
            al_draw_bitmap(charc.img_blood[3], charc.x, charc.y, 0);
            //al_play_sample_instance(chara.atk_Sound);
        }
    }

void monster_blood_destory(){
    al_destroy_bitmap(charc.img_blood[0]);
    al_destroy_bitmap(charc.img_blood[1]);
    al_destroy_bitmap(charc.img_blood[2]);
    al_destroy_bitmap(charc.img_blood[3]);

}

//The state of monster
//Character chard;
ALLEGRO_SAMPLE*samplee = NULL;

void monster_init(){
    for(int i=1;i<=1;i++){
        char tempp[500];
        sprintf( tempp, "./image/monster%d.png",i);
        chard.img_move[i-1] = al_load_bitmap(tempp);
    }

        char tempp[500];
        sprintf( tempp, "./image/monster_atk1.png");
        chard.img_atk[0] = al_load_bitmap(tempp);
        sprintf( tempp, "./image/monster_atk2.png");
        chard.img_atk[1] = al_load_bitmap(tempp);

    // load effective sound
    samplee = al_load_sample("./sound/atk_sound.wav");
    chard.atk_Sound  = al_create_sample_instance(samplee);
    al_set_sample_instance_playmode(chard.atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(chard.atk_Sound, al_get_default_mixer());
    // initial the geometric information of character
    chard.width = al_get_bitmap_width(chard.img_move[0]);
    chard.height = al_get_bitmap_height(chard.img_move[0]);
    chard.x = WIDTH/2;
    chard.y = HEIGHT/2;

    // initial the animation component
    chard.state = STOPP;
    chard.anime = 0;
    chard.anime_time = 30;
}

void monster_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chard.anime++;
            chard.anime %= chard.anime_time;
        }
    }
}
bool collide(int ax1, int ay1,int bx1, int by1)
{
    int ax2 = ax1+164;
    int bx2 = bx1+300;
    int ay2 = ay1+160;
    int by2 = by1+274;
    if(ax1 > bx2) return false;
    if(ax2 < bx1) return false;
    if(ay1 > by2) return false;
    if(ay2 < by1) return false;

    return true;
}

void monster_update(){
    if(rand() % 150 == 0){
        chard.state = ATKK;
        chard.x -=5;
        chard.y -=3;
    }
    else if(rand() % 200 == 0){
        chard.state = MOVEE;
        chard.x -=5;
        chard.y -=3;
    }
    else if(chard.state == ATKK){//¹ÖÎï¹¥“ôááÍùÖ÷½ÇÇ°ßM
        chard.x -= 5;
        chard.state = MOVEE;
    }else if( chard.anime == chard.anime_time-1 ){
        chard.anime = 0;
        chard.state = STOPP;
    }else if ( chard.anime == 0 ){
        chard.state = STOPP;
    }
    if(collide(chara.x,chara.y,chard.x,chard.y)){//¹ÖÎï±»Ö÷½Ç¹¥“ôáá¹¥“ôÖ÷½Ç
        if(chara.state==ATK&&rand() % 10 == 0){
            chard.state = ATKK;
            monster_hp+=aatk;
        }
    }

}

void monster_draw(){
    // with the state, draw corresponding image
    if( chard.state == STOPP ){
            al_draw_bitmap(chard.img_move[0], chard.x, chard.y, 0);
    }
    else if( chard.state == MOVEE ){

            if( chard.anime < chard.anime_time/2){
                al_draw_bitmap(chard.img_move[0], chard.x, chard.y, 0);
            }else{
                al_draw_bitmap(chard.img_move[0], chard.x, chard.y, 0);
            }
        }
    else if( chard.state == ATKK){

            if( chard.anime < chard.anime_time/2 ){
                al_draw_bitmap(chard.img_atk[0], chard.x, chard.y, 0);
            }else{
                al_draw_bitmap(chard.img_atk[1], chard.x, chard.y, 0);
                al_play_sample_instance(chard.atk_Sound);
            }
        }
    }

void monster_destory(){
    al_destroy_bitmap(chard.img_atk[0]);
    al_destroy_bitmap(chard.img_atk[1]);
    al_destroy_bitmap(chard.img_move[0]);
    al_destroy_bitmap(chard.img_move[1]);
    al_destroy_sample_instance(chard.atk_Sound);
}





