// a dinky little game where you move the circle to the x and get a point
// idk i was bored
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WIDTH 80
#define MAX_HEIGHT 20

bool nextLocation(int* location);
void randomLocation(int* location);

int main(int argc, char* argv[]) {
    srand(time(NULL));

    int location[2] = {MAX_WIDTH / 2, MAX_HEIGHT / 2};
    int randomSpot[2] = {0, 0};
    int points = 0;

    initscr();
    clear();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    int none[2] = {0, 0};
    while (nextLocation(none)) {
        clear();
        mvprintw(MAX_HEIGHT / 2, MAX_WIDTH / 2, "welcome to The Game!");
        mvprintw(MAX_HEIGHT / 2 + 1, MAX_WIDTH / 2 - 15, "the object of the game is to get as many points as you can.");
        mvprintw(MAX_HEIGHT / 2 + 2, MAX_WIDTH / 2 - 5, "to start the game, press x now!");
        refresh();
    }

    randomLocation(randomSpot);

    while (nextLocation(location)) {
        clear();
        char message[90] = "The Game || use the arrow keys to move || press x to exit || points: ";
        char strPoints[12];
        sprintf(strPoints, "%d", points);
        strncat(message, strPoints, 12);

        mvprintw(0, 0, message);
        mvprintw(randomSpot[1], randomSpot[0], "X");
        mvprintw(location[1], location[0], "O");

        if (location[1] == randomSpot[1] && location[0] == randomSpot[0]) {
            points++;
            randomLocation(randomSpot);
            randomLocation(location);
        }

        for (size_t i = 0; i < MAX_WIDTH; i++) {
            mvprintw(MAX_HEIGHT, i, "^");
        }

        refresh();
    }
    endwin();
}

// nextLocation sets location according to key input, and returns true if key input != x
bool nextLocation(int* location) {
    int ch;
    bool retval = true;
    if ((ch = getch()) != ERR) {
        switch (ch) {
            case KEY_LEFT:
                if (location[0] - 1 > 0) {
                    location[0] -= 1;
                } else {
                    location[0] = MAX_WIDTH - 1;
                }
                break;
            case KEY_RIGHT:
                if (location[0] + 1 < MAX_WIDTH) {
                    location[0] += 1;
                } else {
                    location[0] = 1;
                }
                break;
            case KEY_UP:
                if (location[1] - 1 > 0) {
                    location[1] -= 1;
                } else {
                    location[1] = MAX_HEIGHT - 1;
                }
                break;
            case KEY_DOWN:
                if (location[1] + 1 < MAX_HEIGHT) {
                    location[1] += 1;
                } else {
                    location[1] = 1;
                }
                break;
            case 120:  // X key
                retval = false;
        }
    }
    return retval;
}

// randomLocation sets location to a random location on the board, not on the 0 plane
void randomLocation(int* location) {
    do {
        location[0] = (rand() % MAX_WIDTH);
    } while (!location[0]);
    do {
        location[1] = (rand() % MAX_HEIGHT);
    } while (!location[1]);
}