#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse_cursor.h>
#include <math.h>
#include <iostream>

int main() {

    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();


    ALLEGRO_DISPLAY* display = al_create_display(640, 480);
    al_set_window_position(display, 200, 200);

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    ALLEGRO_COLOR corMira = al_map_rgb(255, 255, 255);

    ALLEGRO_BITMAP* persona = al_load_bitmap("persona.png");

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_start_timer(timer);

    float posX = 0, posY = 0;
    float mouseX = 0, mouseY = 0;
    float rad = 0.00;

    float hip = sqrt(pow(mouseX, 2) + pow(mouseY, 2));
    float ang = mouseX / hip;

    rad = ang * (3.1415 / 180);

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouseX = event.mouse.x;
            mouseY = event.mouse.y;
        }

        posX = cos(mouseX);
        posY = sin(mouseY);


        

        printf("MouseX:%f MouseY:%f", mouseX,mouseY);

        //al_draw_bitmap(persona, 310,230,0);
        al_draw_filled_rectangle(mouseX - 1, mouseY - 2, mouseX + 2, mouseY - 15, al_map_rgb(255, 0, 0)); //Miras Verticais
        al_draw_filled_rectangle(mouseX - 1, mouseY + 2, mouseX + 2, mouseY + 15, al_map_rgb(255, 0, 0));

        al_draw_filled_rectangle(mouseX + 2, mouseY - 1, mouseX + 15, mouseY + 2, al_map_rgb(255, 0, 0)); //Miras Horizontais
        al_draw_filled_rectangle(mouseX - 2, mouseY - 1, mouseX - 15, mouseY + 2, al_map_rgb(255, 0, 0));

        al_draw_rotated_bitmap(persona, 10, 10, 310, 230, rad, 0);

        rad = mouseY/mouseX;

        al_flip_display();
        al_clear_to_color(al_map_rgb(255, 255, 255));
    }
    al_destroy_bitmap(persona);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
