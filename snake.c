#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#define MAX_SNAKE_LENGTH 100

int main() {
	int screen_height = 20;
	int screen_width = 40;

	WINDOW *win = initscr();
	keypad(win, true);
	nodelay(win, true);
	curs_set(0);

	int snake_length = 1;

	int snake_x[MAX_SNAKE_LENGTH] = {1};
	int snake_y[MAX_SNAKE_LENGTH] = {1};

	int direction_x = 0; 
	int direction_y = 1;

    int food_x = (rand() % ((screen_width - 2)/ 2)) *2 + 1; 
    int food_y = rand() % (screen_height - 2) + 1;

	while(true) {
		int pressed = wgetch(win);
		
		if (pressed == KEY_LEFT){
			if(direction_x == 1) {
				continue;
			}
			direction_x = -1;
			direction_y = 0;
		}

		if (pressed == KEY_RIGHT){
			if(direction_x == -1) {
				continue;
			}
			direction_x = 1;
			direction_y = 0;
		}
		
		if (pressed == KEY_UP){
				if(direction_y == 1) {
				continue;
			}
		direction_x = 0;
			direction_y = -1;
		}
		
		if (pressed == KEY_DOWN){
				if(direction_y == -1) {
				continue;
			}
			direction_x = 0;
			direction_y = 1;
		}
		if (pressed == '\e'){
			break;
		}

		int new_head_x = snake_x[0] + direction_x *2;
		int new_head_y = snake_y[0] + direction_y;

		if (new_head_x<=0 || new_head_x >= screen_width-1 || new_head_y <= 0 || new_head_y>= screen_height-1) {
		mvprintw(screen_height / 2, (screen_width - 15) / 2, "Game Over! Your score:%d", snake_length-1);
			refresh();
			usleep(2000000);
			break;
		}

		for (int i = 0; i<snake_length; i++) {
		if (snake_x[i] == new_head_x  && snake_y[i] == new_head_y) {
		mvprintw(screen_height / 2, (screen_width - 15) / 2, "Game Over! Your score:%d", snake_length-1);
			refresh();
			usleep(2000000);
			break;
		}
		}
	for (int i = snake_length - 1; i > 0; i--) {
            snake_x[i] = snake_x[i - 1];
            snake_y[i] = snake_y[i - 1];
        }
		snake_x[0] = new_head_x;
	        snake_y[0] = new_head_y;

	
	if (snake_x[0] == food_x && snake_y[0] == food_y) {
            snake_length++;
		food_x = (rand() % ((screen_width - 2) / 2)) * 2 + 1;
            food_y = rand() % (screen_height - 2) + 1;
        }

		erase();
		
		for (int i=0; i< screen_width; i++) {
		mvaddch(0, i, '#');
		mvaddch((screen_height), i, '#');
		}
		for (int i=1; i< screen_height; i++) {
		mvaddch(i , 0, '#');
		mvaddch(i , (screen_width), '#');
		}
		mvaddch(food_y, food_x, '$');

		for (int i=0; i<snake_length; i++) {
		mvaddch(snake_y[i], snake_x[i], 'O');
		}

		usleep(100000);
	}
	endwin();
	return 0;
}
