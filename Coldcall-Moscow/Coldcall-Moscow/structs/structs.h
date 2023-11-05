#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>


#ifndef strucs_h
#define structs_h

typedef struct personagem {

    ALLEGRO_BITMAP* img;
    float posicaoX, posicaoY;
    bool vida;
    int equip;

}personagemPrincipal;


#endif structs_h
