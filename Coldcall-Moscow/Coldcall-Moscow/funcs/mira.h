#include <iostream>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#ifndef mira_h
#define mira_h

void mira(float *mouseX, float *mouseY, ALLEGRO_DISPLAY* tela) {

    al_hide_mouse_cursor(tela);

    al_draw_filled_rectangle(*mouseX - 1, *mouseY - 2, *mouseX + 2, *mouseY - 15, al_map_rgb(255, 0, 0)); //Miras Verticais
    al_draw_filled_rectangle(*mouseX - 1, *mouseY + 2, *mouseX + 2, *mouseY + 15, al_map_rgb(255, 0, 0));

    al_draw_filled_rectangle(*mouseX + 2, *mouseY - 1, *mouseX + 15, *mouseY + 2, al_map_rgb(255, 0, 0)); //Miras Horizontais
    al_draw_filled_rectangle(*mouseX - 2, *mouseY - 1, *mouseX - 15, *mouseY + 2, al_map_rgb(255, 0, 0));

}

#endif mira_h