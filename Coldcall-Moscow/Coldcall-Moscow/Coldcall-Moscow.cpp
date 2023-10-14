#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse_cursor.h>
#include <iostream>

int main() {

    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();

    ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
    al_set_window_position(display, 300, 300);

    ALLEGRO_TIMER * timer = al_create_timer(1.0 / 60.0);

    ALLEGRO_COLOR corMira = al_map_rgb(255, 255, 255);

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_start_timer(timer);

    int posicaoX = 300, posicaoY = 300;
    int mouseX = 0, mouseY = 0;

    int keyDPressed = false, keyAPressed = false, keyWPressed = false, keySPressed = false;
    int velocidade = 3;

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_D) {
                keyDPressed = true; 
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_A) {
                keyAPressed = true; 
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_W) {
                keyWPressed = true; 
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_S) {
                keySPressed = true; 
            }
        } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            if (event.keyboard.keycode == ALLEGRO_KEY_D) {
                keyDPressed = false; 
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_A) {
                keyAPressed = false; 
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_W) {
                keyWPressed = false; 
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_S) {
                keySPressed = false; 
            }
        }

        if (keyDPressed && !keyAPressed && !keyWPressed && !keySPressed) {
            posicaoX += velocidade;
        }
        if (keyAPressed && !keyDPressed && !keyWPressed && !keySPressed) {
            posicaoX -= velocidade;
        }
        if (keyWPressed && !keyAPressed && !keyDPressed && !keySPressed) {
            posicaoY -= velocidade;
        }
        if (keySPressed && !keyAPressed && !keyDPressed && !keyWPressed) {
            posicaoY += velocidade;
        }

        if (keyDPressed && keySPressed && !keyAPressed && !keyWPressed) {
            double normalizacao = sqrt(posicaoX * posicaoX + posicaoY * posicaoY);
            double normaX = posicaoX / normalizacao;
            double normaY = posicaoY / normalizacao;
            posicaoX += normaX * velocidade;
            posicaoY += normaY * velocidade;
        }
        if (keyDPressed && keyWPressed && !keyAPressed && !keySPressed) {
            double normalizacao = sqrt(posicaoX * posicaoX + posicaoY * posicaoY);
            double normaX = posicaoX / normalizacao;
            double normaY = posicaoY / normalizacao;
            posicaoX += normaX * velocidade;
            posicaoY -= normaY * velocidade;
        }
        if (keyAPressed && keyWPressed && !keyDPressed && !keySPressed) {
            double normalizacao = sqrt(posicaoX * posicaoX + posicaoY * posicaoY);
            double normaX = posicaoX / normalizacao;
            double normaY = posicaoY / normalizacao;
            posicaoX -= normaX * velocidade;
            posicaoY -= normaY * velocidade;
        }
        if (keyAPressed && keySPressed && !keyDPressed && !keyWPressed) {
            double normalizacao = sqrt(posicaoX * posicaoX + posicaoY * posicaoY);
            double normaX = posicaoX / normalizacao;
            double normaY = posicaoY / normalizacao;
            posicaoX -= normaX * velocidade;
            posicaoY += normaY * velocidade;
        }
        
        
        if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouseX = event.mouse.x;
            mouseY = event.mouse.y;
        }

        al_clear_to_color(al_map_rgb(255, 255, 255));

        al_draw_filled_rectangle(0 + pos_x, 0 + pos_y, 20 + pos_x, 20 + pos_y, al_map_rgb(255, 0, 0));
        al_flip_display();
        al_clear_to_color(al_map_rgb(255, 255, 255));
    }

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
