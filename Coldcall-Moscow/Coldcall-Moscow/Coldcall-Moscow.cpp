#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse_cursor.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <math.h>
#include "structs/structs.h"
#include "funcs/movimento.h"
#include "funcs/mira.h"


personagemPrincipal persona;

int main() {
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();

    ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
    al_set_window_position(display, 300, 300);

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    ALLEGRO_BITMAP* background = al_load_bitmap("./telas/background.jpeg");
    persona.img = al_load_bitmap("./sprites/personagem.png");

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_start_timer(timer);

    persona.posicaoX = 300, persona.posicaoY = 300;
    float posicaoMouseX = 0, posicaoMouseY = 0;
    float mouseX = 0, mouseY = 0;

    int keyDPressed = false, keyAPressed = false, keyWPressed = false, keySPressed = false;
    int velocidade = 3;
    float ang = 0;

    int cameraX = 0, cameraY = 0;


    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        
        movimentoPersonagem(&keyWPressed, &keyAPressed, &keySPressed, &keyDPressed, &persona.posicaoX,&persona.posicaoY, velocidade); 
        //Realiza a movimentação do personagem pelas teclas

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_D:
                keyDPressed = true;
                break;
            case ALLEGRO_KEY_A:
                keyAPressed = true;
                break;
            case ALLEGRO_KEY_W:
                keyWPressed = true;
                break;
            case ALLEGRO_KEY_S:
                keySPressed = true;
                break;
            default:
                break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_D:
                keyDPressed = false;
                break;
            case ALLEGRO_KEY_A:
                keyAPressed = false;
                break;
            case ALLEGRO_KEY_W:
                keyWPressed = false;
                break;
            case ALLEGRO_KEY_S:
                keySPressed = false;
                break;
            default:
                break;
            }
        }
        // Detecta entrada do teclado

        if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouseX = event.mouse.x;
            mouseY = event.mouse.y;
        }
        // Detecta entrada do mosue
 
        if (persona.posicaoX < -2.5) {
            persona.posicaoX = -2.5;
        }
        if (persona.posicaoY < -2.5) {
            persona.posicaoY = -2.5;
        }
        if (persona.posicaoX > 1262.5) {
            persona.posicaoX = 1262.5;
        }
        if (persona.posicaoY > 702.5) {
            persona.posicaoY = 702.5;
        }
        // Limites mapa

        posicaoMouseX = mouseX - (al_get_display_width(display)) / 2;
        posicaoMouseY = -1 * (mouseY - (al_get_display_height(display) / 2));
        ang = atan2(posicaoMouseX, posicaoMouseY);

        cameraX = persona.posicaoX - al_get_display_width(display) / 2;
        cameraY = persona.posicaoY - al_get_display_height(display) / 2;

        al_clear_to_color(al_map_rgb(255, 255, 255));

        al_draw_bitmap(background, 0 - cameraX, 0 - cameraY, 0);

        mira(&mouseX, &mouseY, display);
        //Mira em volta do mouse

        al_draw_rotated_bitmap(persona.img, 10, 10, persona.posicaoX - cameraX, persona.posicaoY - cameraY, ang, 0);

        al_flip_display();
        al_clear_to_color(al_map_rgb(255, 255, 255));
    }
    al_destroy_bitmap(background);
    al_destroy_bitmap(persona.img);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}