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
        } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
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

        if (keyDPressed && !keyAPressed && !keyWPressed && !keySPressed) {
            posicaoX += velocidade;
        }else if (keyAPressed && !keyDPressed && !keyWPressed && !keySPressed) {
            posicaoX -= velocidade;
        }else if (keyWPressed && !keyAPressed && !keyDPressed && !keySPressed) {
            posicaoY -= velocidade;
        }else if (keySPressed && !keyAPressed && !keyDPressed && !keyWPressed) {
            posicaoY += velocidade;
        }

        if (keyDPressed && keySPressed && !keyAPressed && !keyWPressed) {
            double normalizacao = sqrt(posicaoX * posicaoX + posicaoY * posicaoY);
            double normaX = posicaoX / normalizacao;
            double normaY = posicaoY / normalizacao;
            posicaoX += normaX * velocidade;
            posicaoY += normaY * velocidade;
        }else if (keyDPressed && keyWPressed && !keyAPressed && !keySPressed) {
            double normalizacao = sqrt(posicaoX * posicaoX + posicaoY * posicaoY);
            double normaX = posicaoX / normalizacao;
            double normaY = posicaoY / normalizacao;
            posicaoX += normaX * velocidade;
            posicaoY -= normaY * velocidade;
        }else if (keyAPressed && keyWPressed && !keyDPressed && !keySPressed) {
            double normalizacao = sqrt(posicaoX * posicaoX + posicaoY * posicaoY);
            double normaX = posicaoX / normalizacao;
            double normaY = posicaoY / normalizacao;
            posicaoX -= normaX * velocidade;
            posicaoY -= normaY * velocidade;
        }else if (keyAPressed && keySPressed && !keyDPressed && !keyWPressed) {
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

        al_draw_filled_rectangle(mouseX - 1, mouseY - 2, mouseX + 2, mouseY - 15, al_map_rgb(255, 0, 0)); //Miras Verticais
        al_draw_filled_rectangle(mouseX - 1, mouseY + 2, mouseX + 2, mouseY + 15, al_map_rgb(255, 0, 0));

        al_draw_filled_rectangle(mouseX + 2, mouseY - 1, mouseX + 15, mouseY + 2, al_map_rgb(255, 0, 0)); //Miras Horizontais
        al_draw_filled_rectangle(mouseX - 2, mouseY - 1, mouseX - 15, mouseY + 2, al_map_rgb(255, 0, 0));

        al_draw_filled_rectangle(0 + posicaoX, 0 + posicaoY, 20 + posicaoX, 20 + posicaoY, al_map_rgb(255, 0, 0));

        al_flip_display();
        al_clear_to_color(al_map_rgb(255, 255, 255));
    }

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
