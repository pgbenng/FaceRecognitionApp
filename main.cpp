#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int height = 20;
const int width = 20;

int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100], nTail;

enum eDirection {STOP = 0, UP, DOWN, LEFT, RIGHT};
eDirection dir;

void setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = width / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
}

void draw() {
    system("CLS");
    for (int i = 0; i < width; i++) {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1) {
                cout << "#";
            } else if (i == y && j == x){
                cout << "O";
            } else if (i == fruitY && j == fruitX) {
                cout << "F";
            } else {
                bool print = false;

                for (int k = 0; k < nTail; k++) {
                    if (i == tailY[k] && j == tailX[k]) {
                        cout << "o";
                        print = true;
                    }
                } if (!print) cout << " ";
            }
        } cout << endl;
    }

    for (int i = 0; i < width; i++) {
        cout << "#";
    }
    cout << endl;
    cout << endl;
    cout << "Score: " << score << endl;
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w': {
                dir = UP;
                break;
            }
            case 'a': {
                dir = LEFT;
                break;
            }
            case 's': {
                dir = DOWN;
                break;
            }
            case 'd': {
                dir = RIGHT;
                break;
            }
            default:
                break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    int prev2X, prev2Y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case UP:
            y--;
            Sleep(400);
            break;
        case DOWN:
            y++;
            Sleep(400);
            break;
        case LEFT:
            x--;
            Sleep(200);
            break;
        case RIGHT:
            x++;
            Sleep(200);
            break;
        default:
            break;
    }

    if (x < 0 || x > width || y < 0 || y > height) {
        gameOver = true;
    }

    for (int i = 0; i < nTail; i++) {
        if (x == tailX[i] && y == tailY[i]) {
            gameOver = true;
        }
    }
    if (x == fruitX && y == fruitY) {
        score++;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(40);
    }
    return 0;
}
