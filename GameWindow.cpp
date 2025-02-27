#include "GameWindow.h"

bool draw = false;
int window=1;
int hp =100;
int monster_hp=0;
int aatk = 1; //§ðÀ»¤O
int money=0;
int win_state=0;
int a=1;
int b=3;
int c=5;

const char *title = "Final Project ";

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_SAMPLE *song=NULL;
ALLEGRO_SAMPLE_INSTANCE *sample_instance;

int Game_establish() { //step 1
int msg = 0;

    game_init();
    game_begin();

    while ( msg != GAME_TERMINATE ) {
        msg = game_run();
        if ( msg == GAME_TERMINATE )
            printf( "Game Over\n" );
    }

    game_destroy();
    return 0;
}

void game_init() { //step 2
    printf( "Game Initializing...\n" );
    al_init();
    // init audio
    al_install_audio();
    al_init_acodec_addon();
    // Create display
    display = al_create_display(WIDTH, HEIGHT);
    // create event queue
    event_queue = al_create_event_queue();
    // Initialize Allegro settings
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event
    // Register event
    al_register_event_source(event_queue, al_get_display_event_source( display ));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    fps  = al_create_timer( 1.0 / FPS );
    al_register_event_source(event_queue, al_get_timer_event_source( fps )) ;
    // initialize the icon on the display
    ALLEGRO_BITMAP *icon = al_load_bitmap("./image/iconn.png");
    al_set_display_icon(display, icon);
}

void game_begin() {  //step 3
    // Load sound
    song = al_load_sample("./sound/hello1.mp3");
    al_reserve_samples(20);
    sample_instance = al_create_sample_instance(song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(sample_instance, 1) ;
    al_play_sample_instance(sample_instance);
    al_start_timer(fps);
    // initialize the menu before entering the loop
    menu_init();  //step 4

}
void game_update(){ //step 8
    //printf("y");
    if( judge_next_window ){

        //printf("place:%d\n",place);

        //menu
        if( place == 5 ){
            store_scene_destroy();
            menu_init();
            menu_draw();
            judge_next_window = false;
            window = 1;
            draw=true;
            //printf("place=5.win=1--yes,draw:%d\n",draw);
            //place = 2;
            //draw = true;

        }
         if( place == 6 ){
            game_scene_destroy();
            menu_init();
            menu_draw();
            judge_next_window = false;
            window = 1;
            draw=true;
            //printf("place=6.win=1--yes,draw:%d\n",draw);
            //place = 2;
            //draw = true;

        }
        if( place == 7 ){
            game_scene_destroy();
            fin_init();
            fin_draw();
            judge_next_window = false;
            window = 4;
            draw = true;
        }
        //fight
        if( place == 1 ){
            // not back menu anymore, therefore destroy it
            menu_destroy();
            // initialize next scene
            game_scene_init();
            judge_next_window = false;
            window = 2;
        }

        //store
        if( place == 2 ){
            // not back menu anymore, therefore destroy it
            menu_destroy();
            // initialize next scene
            store_scene_init();
            judge_next_window = false;
            window = 3;
        }

        //restart
        if( place == 3 ){
            // not back menu anymore, therefore destroy it
            menu_destroy();
            menu_init();
            draw = false;
            window=1;
            hp = 10;
            monster_hp=5;
            aatk = 1;
            money=0;
            win_state=0;
            judge_next_window = false;
            window = 1;
        }

        //exit
        if( place == 4 ){
            // not back menu anymore, therefore destroy it
            menu_destroy();
            // initialize next scene
            printf( "Game Over\n" );
            game_destroy();

        }
    }
    if( window == 2 ){
        charater_update();
        monster_update();
        monster_blood_update();
        hero_blood_update();
    }
     if( window == 3){
        charater_update();
     }
}
int process_event(){  //step 6
    // Request the event
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    // process the event of other component
    if( window == 1 ){//printf("OK\n");
        menu_process(event); //step 7
    }else if( window == 2){
        charater_process(event);
        monster_process(event);
        game_process(event);
    }else if( window == 3){
        store_process(event);
        //printf("tt");
    }

    // Shutdown our program
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return GAME_TERMINATE;
    else if(event.type == ALLEGRO_EVENT_TIMER)
        if(event.timer.source == fps)
            draw = true;
    game_update(); //step 8
    return 0;
}
void game_draw(){
    if( window == 1 ){//printf("yes");
        menu_draw();
    }else if( window == 2 ){
        game_scene_draw();
    }
    al_flip_display(); //更新或複製緩衝區讓畫面可以顯示??
}

void store_draw(){
    if( window == 1 ){
        menu_draw();
    }else if( window == 3 ){
        store_scene_draw();
    }
    al_flip_display();
}

int game_run() {  //step 5
//printf("gamerun\n");
    int error = 0;
    if( draw ){
        if(place==1){
            game_draw();
            draw = false;}
        else if(place==2){
            store_draw();
            draw = false;}
        else if(place == 5){
                //printf("p=5,w=1\n");
            menu_draw();
            draw = false;
            place = 1;
        }
        else if(place==6){
            menu_draw();
            draw=false;
            place=1;
        }else if(place==7){
            fin_draw();
            al_flip_display();
            draw=false;
            //return -1;
        }
    }
    if ( !al_is_event_queue_empty(event_queue) ) { //如果指定的事件隊列當前為空，則返回 true。
        error = process_event(); //step 6
    }
    return error;
}

void game_destroy() {
    // Make sure you destroy all things
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_destroy_sample_instance(sample_instance);
    game_scene_destroy();
}
