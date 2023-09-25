#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>

int main() {

    al_init();
    al_init_primitives_addon();
    al_install_keyboard();

    ALLEGRO_DISPLAY* display = al_create_display(640, 480);
    al_set_window_position(display, 200, 200);

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    int pos_x = 0, pos_y = 0;

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
            pos_x += 10;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
            pos_x -= 10;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
            pos_y -= 10;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
            pos_y += 10;
        }

        al_clear_to_color(al_map_rgb(255, 255, 255));

        al_draw_filled_rectangle(0 + pos_x, 0 + pos_y, 20 + pos_x, 20 + pos_y, al_map_rgb(255, 0, 0));
        al_flip_display();
    }

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
